#ifndef KTP_H
#define KTP_H

struct KTP {
    long long int nik;
    char nama[40];
    char tempat_lahir[25];
    int tanggal;
    int bulan;
    int tahun;
    bool jenis_kelamin;
    char gol_darah[4];
    char alamat[40];
    float rt;
    float rw;
    char kelurahan[20];
    char kecamatan[20];
    char agama[15];
    char status[20];
    char pekerjaan[25];
    char kewarganegaraan[10];
    int berlaku_tahun;
};

#endif

