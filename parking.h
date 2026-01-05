#ifndef PARKING_H
#define PARKING_H

#include <iostream>
#include <string>
using namespace std;

struct ParkingRecord {
    string plate;
    string type; 
    string location;
    int floor;
    int entryHour;
};

class ParkingSystem {
private:
    ParkingRecord* arr;
    int kapasitas;
    int jumlah;
    int nextId; 

    void ensureCapacity() {
        if (jumlah < kapasitas) return;
            int newCap = kapasitas * 2;
            ParkingRecord* tmp = new ParkingRecord[newCap];
        for (int i = 0; i < jumlah; i++) tmp[i] = arr[i];
        delete[] arr;
        arr = tmp;
        kapasitas = newCap;
    }

    string genLocation(int id) {
        
        int idx = id % 50; 
        int row = idx / 10;
        int col = idx % 10 + 1;
        string loc = "";
        loc += char('A' + row);
        if (col < 10) loc += '0';
            loc += to_string(col);
            return loc;
    }

    int indexOfPlate(const string& plate) {
        for (int i = 0; i < jumlah; i++) if (arr[i].plate == plate) return i;
        return -1;
    }

public:
    ParkingSystem(int cap = 100) {
        kapasitas = cap;
        arr = new ParkingRecord[kapasitas];
        jumlah = 0;
        nextId = 0;
    }

    ~ParkingSystem() {
        delete[] arr;
    }

    void parkVehicle(const string& type, const string& plate, int floor, int entryHour) {
        if (indexOfPlate(plate) != -1) {
            cout << "Kendaraan dengan plat " << plate << " sudah terdaftar di parkir.\n";
            return;
        }
        ensureCapacity();
        ParkingRecord r;
        r.type = type;
        r.plate = plate;
        r.floor = floor;
        r.entryHour = entryHour;
        r.location = genLocation(nextId++);
            arr[jumlah++] = r;
            cout << "Parkir berhasil. Lokasi: L" << floor << "-" << r.location << " untuk plat " << plate << "\n";
    }

    void findVehicle(const string& plate) {
        int idx = indexOfPlate(plate);
        if (idx == -1) { cout << "Kendaraan tidak ditemukan.\n"; return; }
        ParkingRecord &r = arr[idx];
        cout << "Ditemukan: plat=" << r.plate << ", type=" << r.type << ", lokasi=L" << r.floor << "-" << r.location << ", masuk pukul " << r.entryHour << "\n";
    }

    void leaveVehicle(const string& plate, int exitHour) {
        int idx = indexOfPlate(plate);
        if (idx == -1) { cout << "Kendaraan tidak ditemukan.\n"; return; }
            ParkingRecord r = arr[idx];
            int hours = exitHour - r.entryHour;
        if (hours <= 0) hours += 24;
        int rate = 0;
        if (r.type == "motor") rate = 2000;
            else 
                if (r.type == "car") rate = 5000;
            else 
                if (r.type == "truck") rate = 8000;
            else rate = 5000; 
            int fee = hours * rate;
            cout << "Kendaraan " << r.plate << " (" << r.type << ") dikeluarkan. Durasi: " << hours << " jam. Tarif per jam: Rp " << rate << ". Total: Rp " << fee << "\n";
        
        for (int i = idx+1; i < jumlah; i++) arr[i-1] = arr[i];
        jumlah--;
    }

    void listAll() {
        if (jumlah == 0) { cout << "Tidak ada kendaraan di parkir.\n"; return; }
        cout << "===== Daftar Parkir =====\n";
        for (int i = 0; i < jumlah; i++) {
            ParkingRecord &r = arr[i];
            cout << i+1 << ". plat=" << r.plate << ", type=" << r.type << ", lokasi=L" << r.floor << "-" << r.location << ", masuk=" << r.entryHour << "\n";
        }
    }
};

#endif
