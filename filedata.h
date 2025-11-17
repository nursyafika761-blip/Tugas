#ifndef filedata_h
#define filedata_h
#define MAX_NAME_LEN 100
#define MAX_PRODI_LEN 50
#define MAX_MK_ID_LEN 10

typedef struct {
    int id;
    char nama[MAX_NAME_LEN];
    char prodi[MAX_PRODI_LEN];
    float ipk;
} Mahasiswa;

typedef struct {
    char id_mk[MAX_MK_ID_LEN];
    char nama[MAX_NAME_LEN];
    int sks;
} Matakuliah;

typedef struct {
    int id_mahasiswa;
    char id_matakuliah[MAX_MK_ID_LEN];
} KRS;

void bersihkanBufferInput();
void bacaDariFileCSV(const char *namaFile);

Matakuliah* inputDataMatakuliah(int *jumlah);
void simpanMatakuliahKeCSV(Matakuliah *mk, int jumlah);

Mahasiswa* inputDataMahasiswa(int *jumlah);
void simpanMahasiswaKeCSV(Mahasiswa *mhs, int jumlah);

KRS* inputDataKRS(int *jumlah);
void simpanKRSKeCSV(KRS *krs, int jumlah);

#endif