#include <iostream>
#include "ktp.h"
#include "array1d.h"
#include "linkedlist.h"

using namespace std;

KTP inputKTP() {
    KTP x;

    cout << "NIK               : ";
    cin >> x.nik;
    cin.ignore();

    cout << "Nama              : ";
    cin.getline(x.nama, 40);

    cout << "Tempat Lahir      : ";
    cin.getline(x.tempat_lahir, 20);

    cout << "Tanggal Lahir (1-31): ";
    cin >> x.tanggal;

    cout << "Bulan Lahir (1-12)  : ";
    cin >> x.bulan;

    cout << "Tahun Lahir         : ";
    cin >> x.tahun;

	cout << "Jenis Kelamin // 1=Laki-laki || 0=Perempuan: ";
	cin >> x.jenis_kelamin;
	cin.ignore();


    cout << "Golongan Darah     : ";
    cin.getline(x.gol_darah, 4);

    cout << "Alamat             : ";
    cin.getline(x.alamat, 40);

    cout << "RT                 : ";
    cin >> x.rt;
    cin.ignore();

    cout << "RW                 : ";
    cin >> x.rw;
    cin.ignore();

    cout << "Kelurahan/Desa     : ";
    cin.getline(x.kelurahan, 20);

    cout << "Kecamatan          : ";
    cin.getline(x.kecamatan, 20);

    cout << "Agama              : ";
    cin.getline(x.agama, 15);

    cout << "Status Kawin       : ";
    cin.getline(x.status, 20);

    cout << "Pekerjaan          : ";
    cin.getline(x.pekerjaan, 25);

    cout << "Kewarganegaraan    : ";
    cin.getline(x.kewarganegaraan, 5);

    cout << "Berlaku Hingga Tahun : ";
    cin >> x.berlaku_tahun;

    cin.ignore();
    return x;
}


int main() {
    KTPArray arr;
    LinkedList list;
    int pilih;
    const char* DBFILE = "ktp_manajemen_Mall.txt";

    int loaded = arr.loadFromFile(DBFILE);
    for (int i = 0; i < loaded; i++) {
        list.tambah(arr.data[i]);
    }
    if (loaded > 0) cout << loaded << " record dimuat dari " << DBFILE << "\n";

    do {
        cout << "\n===== MENU KTP =====\n";
        cout << "1. Input Data KTP\n";
        cout << "2. Tampilkan (Array)\n";
        cout << "3. Tampilkan (Linked List)\n";
        cout << "4. Keluar\n";
        cout << "Pilih: ";
        cin >> pilih;

        if (pilih == 1) {
            KTP d = inputKTP();
            arr.tambah(d);
            list.tambah(d);
            arr.saveAppend(DBFILE, d);
            cout << "Disimpan!\n";
        }
        else if (pilih == 2) arr.tampil();
        else if (pilih == 3) list.tampil();

    } while (pilih != 4);

    return 0;
}

