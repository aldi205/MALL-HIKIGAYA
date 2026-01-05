#include <iostream>
#include <string>
#include "menu.h"
#include "transaksi.h"
#include "parking.h"
#include "stores_data.h"
#include "array1d.h"
#include <cctype>
using namespace std;

void lantaiOutfit() {
    TokoOutfit tokoArr[7];
    for (int s = 0; s < 7; s++) tokoArr[s] = TokoOutfit(string(floor1Stores[s].name), 50);
    HistoryManager history(500);
    Queue antrian(20);

    // populate tokoArr from stores_data.h (floor1Stores)
    for (int s = 0; s < 7; s++) {
        for (int i = 0; i < 8; i++) {
            RawItem ri = floor1Stores[s].items[i];
            tokoArr[s].tambahOutfit(ri.name, ri.category, ri.brand, ri.color, ri.size, ri.price, ri.stock);
        }
    }

    int pilih;
    do {
        cout << "\n===== LANTAI 1 : TOKO OUTFIT =====\n";
        cout << "1. Tambah Outfit\n";
        cout << "2. Lihat Outfit (Pilih Brand)\n";
        cout << "3. Tambah Pembeli ke Antrian\n";
        cout << "4. Layani Pembeli\n";
        cout << "5. Lihat Antrian\n";
        cout << "6. Lihat History\n";
        cout << "7. Tambah Stok Barang\n";
        cout << "0. Kembali\n";
        cout << "Pilih: ";
        cin >> pilih;

        switch (pilih) {
        case 1: {
            cout << "Pilih brand (1-7):\n";
            for (int i = 0; i < 7; i++) cout << i+1 << ". " << tokoArr[i].getStoreName() << "\n";
            int b; cin >> b; if (b < 1 || b > 7) { cout << "Brand tidak valid.\n"; break; }
            int idx = b-1;
            Outfit o;
            cin.ignore(1000, '\n');
            cout << "Nama     : "; getline(cin, o.nama);
            cout << "Kategori : "; getline(cin, o.kategori);
            cout << "Merek    : "; getline(cin, o.merek);
            cout << "Warna    : "; getline(cin, o.warna);
            cout << "Ukuran   : "; cin >> o.ukuran;
            cout << "Harga    : "; cin >> o.harga;
            cout << "Stok awal: "; cin >> o.stok;

            tokoArr[idx].tambahOutfit(o);
            {
                string s = string("Tambah outfit di ") + tokoArr[idx].getStoreName() + ": " + o.nama + " - Rp " + to_string(o.harga) + "\n";
                history.add("Admin", s, 0);
            }
            break;
        }

        case 2: {
            cout << "Pilih brand untuk melihat: \n";
            for (int i = 0; i < 7; i++) cout << i+1 << ". " << tokoArr[i].getStoreName() << "\n";
            int b; cin >> b; if (b < 1 || b > 7) { cout << "Brand tidak valid.\n"; break; }
            tokoArr[b-1].tampil();
            break;
        }

        case 3: {
            string nama;
            cout << "Nama pembeli: ";
            cin.ignore(1000,'\n');
            getline(cin, nama);
            antrian.enqueue(nama);
            break;
        }

        case 4: {
            string pembeli = antrian.dequeue();
            if (pembeli == "") { cout << "Antrian kosong.\n"; break; }

            cout << "Melayani: " << pembeli << endl;
            cout << "Pilih brand yang ingin dibeli: \n";
            for (int i = 0; i < 7; i++) cout << i+1 << ". " << tokoArr[i].getStoreName() << "\n";
            int b; cin >> b; if (b < 1 || b > 7) { cout << "Brand tidak valid.\n"; break; }
            int storeIdx = b-1;

            tokoArr[storeIdx].tampilRingkas();

            int pilihOut;
            int total = 0;
            cout << "Detail pembelian (" << tokoArr[storeIdx].getStoreName() << "):\n";

            // collect selections without decrementing stock yet (use dynamic arrays)
            int selCap = 16;
            int *selIdx = new int[selCap];
            int *selQty = new int[selCap];
            int selCount = 0;

            do {
                cout << "Pilih nomor outfit (0 selesai): "; cin >> pilihOut;
                if (pilihOut == 0) break;
                pilihOut--;
                string namaO = tokoArr[storeIdx].getNama(pilihOut);
                int hargaO = tokoArr[storeIdx].getHarga(pilihOut);
                int stokO = tokoArr[storeIdx].getStok(pilihOut);
                if (namaO == "" || hargaO == -1) { cout << "Pilihan tidak valid.\n"; continue; }
                int qty; cout << "Jumlah (stok tersedia " << stokO << "): "; cin >> qty;
                if (qty > stokO) { cout << "Stok tidak cukup.\n"; continue; }
                if (selCount >= selCap) {
                    int newCap = selCap * 2;
                    int *nIdx = new int[newCap];
                    int *nQty = new int[newCap];
                    for (int _i = 0; _i < selCount; _i++) { nIdx[_i] = selIdx[_i]; nQty[_i] = selQty[_i]; }
                    delete[] selIdx; delete[] selQty; selIdx = nIdx; selQty = nQty; selCap = newCap;
                }
                selIdx[selCount] = pilihOut;
                selQty[selCount] = qty;
                selCount++;
                total += hargaO * qty;
                cout << "- " << namaO << " x" << qty << " (Rp " << hargaO << ")\n";
                cout << "Tambah produk lain? (y/n): "; string yn; cin >> yn; if (yn != "y" && yn != "Y") break;
            } while (true);

            if (total == 0) { cout << "Tidak ada barang dipilih.\n"; delete[] selIdx; delete[] selQty; break; }

            cout << "Total: Rp " << total << "\n";
            cout << "Total yang harus dibayar: Rp " << total << "\n";

            // payment method
            cout << "Pilih metode pembayaran:\n1. Cash\n2. Transfer\nPilih: "; int pmet; cin >> pmet;
            bool paid = false;
            int bayar = 0;
            if (pmet == 1) {
                cout << "Masukkan jumlah bayar (cash): "; cin >> bayar;
                if (bayar < total) { cout << "Uang kurang. Transaksi dibatalkan.\n"; delete[] selIdx; delete[] selQty; break; }
                int kembali = bayar - total;
                cout << "Metode: Cash\nDibayar: Rp " << bayar << ", Kembali: Rp " << kembali << "\n";
                paid = true;
                cout << "Transaksi berhasil. Kembalian: Rp " << kembali << "\n";
            } else if (pmet == 2) {
                const char* banks[4] = {"BRI - 1111111111","BCA - 2222222222","Mandiri - 3333333333","BSI - 4444444444"};
                cout << "Pilih bank untuk transfer:\n";
                for (int i = 0; i < 4; i++) cout << i+1 << ". " << banks[i] << "\n";
                int bi; cin >> bi; if (bi < 1 || bi > 4) { cout << "Bank tidak valid. Transaksi dibatalkan.\n"; delete[] selIdx; delete[] selQty; break; }
                cout << "Silakan transfer ke rekening: " << banks[bi-1] << "\n";
                cout << "Sudah transfer? (y/n): "; string conf; cin >> conf;
                if (conf == "y" || conf == "Y") {
                    paid = true;
                    cout << "Metode: Transfer (" << banks[bi-1] << ")\nDibayar via transfer.\n";
                    cout << "Transfer diterima, transaksi selesai.\n";
                } else {
                    cout << "Transfer belum dikonfirmasi. Transaksi dibatalkan.\n";
                    delete[] selIdx; delete[] selQty;
                    paid = false;
                    break;
                }
            } else {
                cout << "Metode pembayaran tidak dikenal. Transaksi dibatalkan.\n";
            }

            if (!paid) { delete[] selIdx; delete[] selQty; break; }

            
            for (int k = 0; k < selCount; k++) tokoArr[storeIdx].buyItem(selIdx[k], selQty[k]);
           
            history.add(pembeli, "", total);
            delete[] selIdx; delete[] selQty;
            break;
        }

        case 5:
            antrian.tampil();
            break;

        case 6:
            history.tampilAll();
            break;

        case 7: {
            cout << "Pilih brand untuk tambah stok: \n";
            for (int i = 0; i < 7; i++) cout << i+1 << ". " << tokoArr[i].getStoreName() << "\n";
            int b; cin >> b; if (b < 1 || b > 7) { cout << "Brand tidak valid.\n"; break; }
            int storeIdx = b-1;
            tokoArr[storeIdx].tampilRingkas();
            cout << "Pilih nomor item untuk tambah stok: "; int it; cin >> it; it--;
            cout << "Jumlah yang ditambahkan: "; int add; cin >> add;
            if (tokoArr[storeIdx].tambahStok(it, add)) cout << "Stok berhasil ditambah.\n";
            else cout << "Gagal menambah stok.\n";
            break;
        }
        }

    } while (pilih != 0);
}


bool requireKTPLogin() {
    KTPArray arr;
    int loaded = arr.loadFromFile("ktp_manajemen_Mall.txt");
    if (loaded <= 0) { cout << "Tidak ada data KTP. Akses ditolak.\n"; return false; }
    string inputName;
    string password;
    cout << "Masukan nama : ";
    cin >> ws; getline(cin, inputName);
    size_t sp = inputName.find(' ');
    string fn = (sp == string::npos) ? inputName : inputName.substr(0, sp);
    cout << "Password : ";cin>> password;

    auto lower = [](string s){ for (size_t i=0;i<s.size();++i) s[i] = std::tolower((unsigned char)s[i]); return s; };
    string want = lower(fn);

    for (int i = 0; i < loaded; i++) {
        string nama = string(arr.data[i].nama);
        size_t sp2 = nama.find(' ');
        string kn = (sp2 == string::npos) ? nama : nama.substr(0, sp2);
        if (lower(kn) == want) {
            long long nik = arr.data[i].nik;
            int last3 = (int)(nik % 1000);
            int passNum = -1;
            try { passNum = std::stoi(password); } catch(...) { passNum = -1; }
            if (passNum == last3) {
                cout << "SELAMAT DATANG BOSSS!!\n";
                return true;
            }
        }
    }
    cout << "Login gagal.\n";
    return false;
}

void lantaiMakan() {
    Menu menuArr[7];
    Queue antrian(50);
    HistoryManager historyMakan(200);

    
    for (int s = 0; s < 7; s++) {
        for (int i = 0; i < 8; i++) {
            RawItem ri = floor2Stores[s].items[i];
            menuArr[s].tambahMenu(ri.name, ri.price);
        }
    }

    int pilih;

    do {
        cout << "\n===== LANTAI 2 : WARUNG MAKAN =====\n";
        cout << "1. Lihat Menu (Pilih Brand)\n";
        cout << "2. Tambah Menu ke Brand\n";
        cout << "3. Tambah Antrian\n";
        cout << "4. Layani Pelanggan\n";
        cout << "5. Lihat Antrian\n";
        cout << "6. Refund (denda potongan 10%)\n";
        cout << "7. Riwayat Pembelian\n";
        cout << "0. Kembali\n";
        cout << "Pilih: ";
        cin >> pilih;

        switch (pilih) {
        case 1: {
            cout << "Pilih brand: \n";
            for (int i = 0; i < 7; i++) cout << i+1 << ". " << floor2Stores[i].name << "\n";
            int b; cin >> b; if (b < 1 || b > 7) { cout << "Brand tidak valid.\n"; break; }
            menuArr[b-1].tampilMenu();
            break;
        }

        case 2: {
            cout << "Pilih brand untuk menambahkan menu: \n";
            for (int i = 0; i < 7; i++) cout << i+1 << ". " << floor2Stores[i].name << "\n";
            int b; cin >> b; if (b < 1 || b > 7) { cout << "Brand tidak valid.\n"; break; }
            string n; int h;
            cout << "Nama menu: "; cin.ignore(1000,'\n'); getline(cin, n);
            cout << "Harga: "; cin >> h;
            menuArr[b-1].tambahMenu(n, h);
            break;
        }

        case 3: {
            string namaP;
            cout << "Nama pelanggan: "; cin.ignore(1000,'\n'); getline(cin, namaP);
            antrian.enqueue(namaP);
            break;
        }

        case 4: {
            string p = antrian.dequeue();
            if (p == "") { cout << "Antrian kosong.\n"; break; }

            cout << "Melayani: " << p << endl;
            cout << "Pilih brand untuk pesanan: \n";
            for (int i = 0; i < 7; i++) cout << i+1 << ". " << floor2Stores[i].name << "\n";
            int b; cin >> b; if (b < 1 || b > 7) { cout << "Brand tidak valid.\n"; break; }
            int brandIdx = b-1;

            int meja; cout << "Nomor meja yang diinginkan: "; cin >> meja;

            int pilihMenu = -1;
            int total = 0;
            cout << "Pesanan (" << floor2Stores[brandIdx].name << "):\n";

            do {
                menuArr[brandIdx].tampilMenu();
                cout << "Pilih menu nomor (0 selesai): "; cin >> pilihMenu;
                if (pilihMenu == 0) break;
                pilihMenu--;
                string namaM = menuArr[brandIdx].getNama(pilihMenu);
                int hargaM = menuArr[brandIdx].getHarga(pilihMenu);
                if (hargaM == -1) { cout << "Menu tidak valid!\n"; continue; }
                int qty; cout << "Berapa banyak: "; cin >> qty;
                total += hargaM * qty;
                cout << "- " << namaM << " x" << qty << " (Rp " << hargaM << ")\n";
                cout << "Tambah menu lain dalam transaksi? (y/n): "; string yn; cin >> yn; if (yn != "y" && yn != "Y") break;
            } while (true);
            cout << "Meja: " << meja << "\n";
            cout << "Total: Rp " << total << "\n";
            cout << "Total yang harus dibayar: Rp " << total << "\n";
            cout << "Pilih metode pembayaran:\n1. Cash\n2. Transfer\nPilih: "; int pmet; cin >> pmet;
            bool paid = false;
            if (pmet == 1) {
                int bayar; cout << "Masukkan jumlah bayar (cash): "; cin >> bayar;
                if (bayar < total) { cout << "Uang kurang. Transaksi batal.\n"; break; }
                int kembali = bayar - total;
                cout << "Metode: Cash\nDibayar: Rp " << bayar << ", Kembali: Rp " << kembali << "\n";
                paid = true;
                cout << "Transaksi selesai. Kembalian: Rp " << kembali << "\n";
            } else if (pmet == 2) {
                const char* banks[4] = {"BRI - 1111111111","BCA - 2222222222","Mandiri - 3333333333","BSI - 4444444444"};
                cout << "Pilih bank untuk transfer:\n";
                for (int i = 0; i < 4; i++) cout << i+1 << ". " << banks[i] << "\n";
                int bi; cin >> bi; if (bi < 1 || bi > 4) { cout << "Bank tidak valid. Transaksi dibatalkan.\n"; break; }
                cout << "Silakan transfer ke rekening: " << banks[bi-1] << "\n";
                cout << "Sudah transfer? (y/n): "; string conf; cin >> conf;
                if (conf == "y" || conf == "Y") {
                    paid = true;
                    cout << "Metode: Transfer (" << banks[bi-1] << ")\nDibayar via transfer.\n";
                    cout << "Transfer diterima, transaksi selesai.\n";
                } else {
                    cout << "Transfer belum dikonfirmasi. Transaksi dibatalkan.\n";
                    paid = false;
                }
            } else { cout << "Metode pembayaran tidak dikenal. Transaksi dibatalkan.\n"; }

            if (!paid) break;

            historyMakan.add(p, "", total);
            break;
        }

        case 5:
            antrian.tampil();
            break;

        case 6: {
            int refund = historyMakan.undoWithPenalty(10); // 10% denda
            if (refund == -1) cout << "Tidak ada transaksi untuk di-undo.\n";
            else cout << "Transaksi di-undo. Refund setelah denda: Rp " << refund << "\n";
            break;
        }

        case 7:
            historyMakan.tampilAll();
            break;
        }

    } while (pilih != 0);
}

void miniGameMenu() {
    cout << "\n===== MINI GAME =====\n";
    cout << "1. Tebak Angka\n";
    cout << "2. Suit Batu-Gunting-Kertas\n";
    cout << "3. Quiz\n";
    cout << "4. Typing Speed\n";
    cout << "0. Kembali\n";
    cout << "Pilih: ";
}

int simpleRand(int seed) {
    seed = (seed * 1103515245 + 12345) % 32768;
    return (seed % 10) + 1;
}

int gameTebakAngka() {
    int seed, pilih;
    cout << "\nMasukkan angka (1 sampai 100): ";
    cin >> seed;

    int angka = simpleRand(seed);

    cout << "Tebak angka 1 sampai 10: ";
    cin >> pilih;

    if (pilih == angka) { cout << "Benar!\n"; return 10; }
    else { cout << "Salah! Jawabannya: " << angka << "\n"; return 0; }
}

int gameSuit() {
    string kamu, bot;
    cout << "\nPilih (batu/gunting/kertas): ";
    cin >> kamu;

    int r = simpleRand((int)kamu.length());
    if (r <= 3) bot = "batu";
    else if (r <= 6) bot = "gunting";
    else bot = "kertas";

    cout << "Bot memilih: " << bot << "\n";

    if (kamu == bot) { cout << "Seri!\n"; return 0; }
    else if (
        (kamu == "batu" && bot == "gunting") ||
        (kamu == "gunting" && bot == "kertas") ||
        (kamu == "kertas" && bot == "batu")
    ) { cout << "Kamu menang!\n"; return 5; }
    else { cout << "Kamu kalah!\n"; return 0; }
}

int gameQuiz() {
    string jawab;
    cout << "\nIbukota Indonesia?\nJawab: ";
    cin >> jawab;

    if (jawab == "Jakarta" || jawab == "jakarta") { cout << "Benar!\n"; return 7; }
    else { cout << "Salah! Jawaban: Jakarta\n"; return 0; }
}

int gameTyping() {
    string input;
    cout << "\nKetik kata ini: 'makan'\n> ";
    cin >> input;

    if (input == "makan") { cout << "Benar!\n"; return 3; }
    else { cout << "Salah!\n"; return 0; }
}

void jalankanMiniGame(PointsManager &pm) {
    int p;
    cout << "Masukkan nama pemain mini-game: "; cin.ignore(1000,'\n');
    string pemain; getline(cin, pemain);
    pm.addPlayerIfMissing(pemain);

    do {
        miniGameMenu();
        cin >> p;

        int earned = 0;
        switch (p) {
            case 1: 
                earned = gameTebakAngka();
                 break;
            case 2: 
                earned = gameSuit();
                 break;
            case 3: 
                earned = gameQuiz();
                 break;
            case 4: 
                earned = gameTyping();
                 break;
            case 0: cout << "Kembali...\n";
             break;
                default: cout << "Pilihan tidak valid!\n";
        }
        if (earned > 0) {
            pm.addPoints(pemain, earned);
            cout << "Anda mendapatkan " << earned << " poin. Total poin: " << pm.getPoints(pemain) << "\n";
        }

        if (p == 0) break;

        cout << "Ingin menukarkan hadiah sekarang? (y/n): "; string yn; cin >> yn;
        if (yn == "y" || yn == "Y") {
            pm.showPrizes();
            cout << "Pilih nomor hadiah: "; int h; cin >> h; h--;
            if (pm.redeem(pemain, h)) cout << "Penukaran berhasil. Sisa poin: " << pm.getPoints(pemain) << "\n";
            else cout << "Penukaran gagal (poin tidak cukup atau input salah).\n";
        }

    } while (p != 0);
}

void lantaiBioskopGame() {
    Bioskop bioskop;
    Game game;
    PointsManager pm;

    int pilih;
    do {
        cout << "\n===== LANTAI 3 : BIOSKOP & GAME =====\n";
        cout << "1. Lihat Film\n";
        cout << "2. Pesan Tiket Film\n";
        cout << "3. Lihat Game (daftar)\n";
        cout << "4. Main Game (antri/slot 5 pemain)\n";
        cout << "5. Mini Game (play & redeem hadiah)\n";
        cout << "6. Selesai salah satu pemain (bebaskan slot)\n";
        cout << "7. Tampilkan status game (sedang bermain & antrian)\n";
        cout << "8. Riwayat Bioskop\n";
        cout << "0. Kembali\n";
        cout << "Pilih: ";
        cin >> pilih;

        switch (pilih) {
        case 1:
             bioskop.tampilFilm();
              break;
        case 2:
             bioskop.pesanTiket();
              break;
        case 3:
             game.tampil();
              break;
        case 4:
             game.main();
              break;
        case 5:
             jalankanMiniGame(pm);
              break;
        case 6:
             game.selesaiSatu();
              break;
        case 7:
             game.tampilStatus();
              break;
        case 8:
             bioskop.tampilHistory();
              break;
        }
    } while (pilih != 0);
}

void parkingMenu(ParkingSystem &ps) {
    int p;
    do {
        cout << "\n===== SISTEM PARKIR =====\n";
        cout << "1. Parkir Kendaraan (masuk)\n";
        cout << "2. Cari Kendaraan\n";
        cout << "3. Keluar & Bayar (kembali ke parkir)\n";
        cout << "4. Lihat Semua Parkir\n";
        cout << "0. Kembali\n";
        cout << "Pilih: "; cin >> p;

        switch (p) {
        case 1: {
            cout << "Jenis (motor/car/truck): "; string type; cin >> ws; getline(cin, type);
            cout << "No. plat: "; string plate; getline(cin, plate);
            cout << "Lantai parkir: "; int floor; cin >> floor;
            cout << "Jam masuk (0-23): "; int hour; cin >> hour;
            ps.parkVehicle(type, plate, floor, hour);
            break;
        }
        case 2: {
            cout << "Masukkan no. plat yang dicari: "; string plate; 
            cin >> ws; getline(cin, plate);
            ps.findVehicle(plate);
            break;
        }
        case 3: {
            cout << "Masukkan no. plat yang keluar: "; string plate; 
            cin >> ws; getline(cin, plate);
            cout << "Jam keluar (0-23): "; int hour; 
            cin >> hour;
            ps.leaveVehicle(plate, hour);
            break;
        }
        case 4:
            ps.listAll();
            break;
        }

    } while (p != 0);
}

int main() {
    int pilih;

    do {
        cout << "\n========== MALL HIKIGAYA ==========\n";
           cout << "1. Lantai 1 - Toko Outfit\n";
           cout << "2. Lantai 2 - Warung Makan\n";
           cout << "3. Lantai 3 - Bioskop & Game\n";
           cout << "4. Lihat Catatan Penjualan (memerlukan login)\n";
        cout << "0. Keluar\n";
        cout << "Pilih lantai: ";
        cin >> pilih;

        switch (pilih) {
        case 1:
             lantaiOutfit();
              break;
        case 2:
             lantaiMakan();
              break;
        case 3:
             lantaiBioskopGame();
              break;
           case 4:
               if (requireKTPLogin()) {
                   SalesLog::interactiveMenu();
               } else {
                   cout << "Akses ditolak.\n";
               }
               break;
        }
    } while (pilih != 0);

    cout << "Program selesai.\n";
    return 0;
}

