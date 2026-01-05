#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "ktp.h"
#include <iostream>
using namespace std;

struct Node {
    KTP data;
    Node* next;
};

struct LinkedList {
    Node* head;

    LinkedList() { head = NULL; }

    void tambah(KTP ktp) {
        Node* n = new Node();
        n->data = ktp;
        n->next = NULL;

        if (!head) head = n;
        else {
            Node* p = head;
            while (p->next) p = p->next;
            p->next = n;
        }
    }

    void tampil() {
        cout << "\n=== DATA KTP (Linked List) ===\n";
        Node* p = head;
        while (p) {
            printKTP(p->data);
            p = p->next;
        }
    }

    static void printKTP(KTP d) {
        cout << "\n=========================";

        cout << "\nNIK              : " << d.nik;
        cout << "\nNama             : " << d.nama;
        cout << "\nTTL              : " 
             << d.tempat_lahir << ", "
             << d.tanggal << "-" << d.bulan << "-" << d.tahun;

        if (d.jenis_kelamin == true)
        	cout << "\nJenis Kelamin    : Laki-laki" << endl;
    	else
        	cout << "\nJenis Kelamin    : Perempuan" << endl;
        	
        cout << "\nGol. Darah       : " << d.gol_darah;

        cout << "\nAlamat           : " << d.alamat;
        cout << "\n   RT/RW         : " << d.rt << "/" << d.rw;
        cout << "\n   Kelurahan     : " << d.kelurahan;
        cout << "\n   Kecamatan     : " << d.kecamatan;

        cout << "\nAgama            : " << d.agama;
        cout << "\nStatus           : " << d.status;
        cout << "\nPekerjaan        : " << d.pekerjaan;
        cout << "\nKewarganegaraan  : " << d.kewarganegaraan;
        cout << "\nBerlaku Hingga   : " << d.berlaku_tahun;

        cout << "\n=========================\n";
    }
};

#endif

