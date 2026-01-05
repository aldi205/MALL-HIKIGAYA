#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <string>
using namespace std;

class Menu {
private:
    string* nama;
    int* harga;
    int kapasitas;
    int jumlah;

public:
    Menu(int cap = 20) {
        kapasitas = cap;
        jumlah = 0;
        nama = new string[kapasitas];
        harga = new int[kapasitas];
    }

    void tambahMenu(const string& n, int h) {
        if (jumlah >= kapasitas) {
            cout << "Menu penuh!\n";
            return;
        }
        nama[jumlah] = n;
        harga[jumlah] = h;
        jumlah++;
    }

    void tampilMenu() {
        cout << "\n===== DAFTAR MENU =====\n";
        for (int i = 0; i < jumlah; i++) {
            cout << i+1 << ". " << nama[i] << " - Rp " << harga[i] << endl;
        }
    }

    string getNama(int index) {
        if (index < 0 || index >= jumlah) return "";
        return nama[index];
    }

    int getHarga(int index) {
        if (index < 0 || index >= jumlah) return -1;
        return harga[index];
    }
};

#endif

