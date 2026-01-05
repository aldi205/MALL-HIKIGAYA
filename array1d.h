#ifndef ARRAY1D_H
#define ARRAY1D_H

#include "ktp.h"
#include <iostream>
#include <fstream>
#include <string>

#define MAX_DATA 100

struct KTPArray {
    KTP data[MAX_DATA];
    int size;

    KTPArray() { size = 0; }

    void tambah(KTP ktp) {
        if (size < MAX_DATA) {
            data[size++] = ktp;
        } else {
            printf("Data penuh!\n");
        }
    }

    bool saveAppend(const char* filename, KTP ktp) {
        std::ofstream out(filename, std::ios::app);
        if (!out.is_open()) return false;
        out << ktp.nik << '|' 
            << ktp.nama << '|' 
            << ktp.tempat_lahir << '|' 
            << ktp.tanggal << '|' 
            << ktp.bulan << '|' 
            << ktp.tahun << '|' 
            << (ktp.jenis_kelamin ? 1 : 0) << '|' 
            << ktp.gol_darah << '|' 
            << ktp.alamat << '|' 
            << ktp.rt << '|' 
            << ktp.rw << '|' 
            << ktp.kelurahan << '|' 
            << ktp.kecamatan << '|' 
            << ktp.agama << '|' 
            << ktp.status << '|' 
            << ktp.pekerjaan << '|' 
            << ktp.kewarganegaraan << '|' 
            << ktp.berlaku_tahun << '\n';
        out.close();
        return true;
    }
    int loadFromFile(const char* filename) {
        std::ifstream f(filename);
        if (!f.is_open()) return 0;
        std::string line;
        size = 0;
        while (std::getline(f, line) && size < MAX_DATA) {
            if (!line.empty() && line.back() == '\r') line.pop_back();

            KTP k;
            // defaults
            k.nik = 0; k.tanggal = k.bulan = k.tahun = 0; k.jenis_kelamin = false; k.rt = 0.0f; k.rw = 0.0f; k.berlaku_tahun = 0;
            // clear char arrays
            for (size_t i = 0; i < sizeof(k.nama); i++) k.nama[i] = '\0';
            for (size_t i = 0; i < sizeof(k.tempat_lahir); i++) k.tempat_lahir[i] = '\0';
            for (size_t i = 0; i < sizeof(k.gol_darah); i++) k.gol_darah[i] = '\0';
            for (size_t i = 0; i < sizeof(k.alamat); i++) k.alamat[i] = '\0';
            for (size_t i = 0; i < sizeof(k.kelurahan); i++) k.kelurahan[i] = '\0';
            for (size_t i = 0; i < sizeof(k.kecamatan); i++) k.kecamatan[i] = '\0';
            for (size_t i = 0; i < sizeof(k.agama); i++) k.agama[i] = '\0';
            for (size_t i = 0; i < sizeof(k.status); i++) k.status[i] = '\0';
            for (size_t i = 0; i < sizeof(k.pekerjaan); i++) k.pekerjaan[i] = '\0';
            for (size_t i = 0; i < sizeof(k.kewarganegaraan); i++) k.kewarganegaraan[i] = '\0';

            size_t pos = 0;
            int field = 0;
            while (pos <= line.size() && field <= 17) {
                size_t next = line.find('|', pos);
                std::string token;
                if (next == std::string::npos) {
                    token = line.substr(pos);
                    pos = line.size() + 1;
                } else {
                    token = line.substr(pos, next - pos);
                    pos = next + 1;
                }

                switch (field) {
                    case 0: if (!token.empty()) try { k.nik = std::stoll(token); } catch(...) { k.nik = 0; } break;
                    case 1: { size_t m = token.copy(k.nama, sizeof(k.nama)-1); k.nama[m] = '\0'; } break;
                    case 2: { size_t m = token.copy(k.tempat_lahir, sizeof(k.tempat_lahir)-1); k.tempat_lahir[m] = '\0'; } break;
                    case 3: k.tanggal = token.empty() ? 0 : std::stoi(token); break;
                    case 4: k.bulan = token.empty() ? 0 : std::stoi(token); break;
                    case 5: k.tahun = token.empty() ? 0 : std::stoi(token); break;
                    case 6: k.jenis_kelamin = (!token.empty() && token != "0"); break;
                    case 7: { size_t m = token.copy(k.gol_darah, sizeof(k.gol_darah)-1); k.gol_darah[m] = '\0'; } break;
                    case 8: { size_t m = token.copy(k.alamat, sizeof(k.alamat)-1); k.alamat[m] = '\0'; } break;
                    case 9: k.rt = token.empty() ? 0.0f : std::stof(token); break;
                    case 10: k.rw = token.empty() ? 0.0f : std::stof(token); break;
                    case 11: { size_t m = token.copy(k.kelurahan, sizeof(k.kelurahan)-1); k.kelurahan[m] = '\0'; } break;
                    case 12: { size_t m = token.copy(k.kecamatan, sizeof(k.kecamatan)-1); k.kecamatan[m] = '\0'; } break;
                    case 13: { size_t m = token.copy(k.agama, sizeof(k.agama)-1); k.agama[m] = '\0'; } break;
                    case 14: { size_t m = token.copy(k.status, sizeof(k.status)-1); k.status[m] = '\0'; } break;
                    case 15: { size_t m = token.copy(k.pekerjaan, sizeof(k.pekerjaan)-1); k.pekerjaan[m] = '\0'; } break;
                    case 16: { size_t m = token.copy(k.kewarganegaraan, sizeof(k.kewarganegaraan)-1); k.kewarganegaraan[m] = '\0'; } break;
                    case 17: k.berlaku_tahun = token.empty() ? 0 : std::stoi(token); break;
                }

                field++;
            }

            data[size++] = k;
        }
        f.close();
        return size;
    }

    void tampil() {
        std::cout << "\n=== DATA KTP (Array) ===\n";
        for (int i = 0; i < size; i++)
            printKTP(data[i]);
    }

    static void printKTP(KTP d) {
        std::cout << "\n=========================\n";
        std::cout << "NIK              : " << d.nik << "\n";
        std::cout << "Nama             : " << d.nama << "\n";
        std::cout << "TTL              : " << d.tempat_lahir << ", " << d.tanggal << "-" << d.bulan << "-" << d.tahun << "\n";
        std::cout << "Jenis Kelamin    : " << (d.jenis_kelamin ? "Laki-laki" : "Perempuan") << "\n";
        std::cout << "Gol. Darah       : " << d.gol_darah << "\n";
        std::cout << "Alamat           : " << d.alamat << "\n";
        std::cout << "   RT/RW         : " << d.rt << "/" << d.rw << "\n";
        std::cout << "   Kelurahan     : " << d.kelurahan << "\n";
        std::cout << "   Kecamatan     : " << d.kecamatan << "\n";
        std::cout << "Agama            : " << d.agama << "\n";
        std::cout << "Status           : " << d.status << "\n";
        std::cout << "Pekerjaan        : " << d.pekerjaan << "\n";
        std::cout << "Kewarganegaraan  : " << d.kewarganegaraan << "\n";
        std::cout << "Berlaku Hingga   : " << d.berlaku_tahun << "\n";
        std::cout << "=========================\n";
    }
};

#endif

