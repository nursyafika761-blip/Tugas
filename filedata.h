#ifndef FILEDATA_H
#define FILEDATA_H

#include <stdio.h> 
#include <stdbool.h> 

// Konstanta (TETAP SAMA)

#define MAX_MATKUL 100
#define MAX_MHS 100
#define MAX_KRS 100

// --- Struktur Data (TETAP SAMA) ---

// Struktur Matakuliah
typedef struct {
	char kode[10];
	char nama[100];
	int sks;
} Matakuliah;

// Struktur Mahasiswa
typedef struct {
	char nim[20];
	char nama[100];
	char prodi[50];
	float ipk;
} Mahasiswa;

// Struktur KRS
typedef struct {
	char nim_mhs[20];
	char kode_mk[10];
	char semester[20];
} KRS;

// Prototipe Fungsi Implementasi Modul
void jalankan_modul_mk();
void jalankan_modul_mhs();
void jalankan_modul_krs(const Mahasiswa *mhs_terpilih);
void clear_input_buffer();
void get_string_input(char *dest, int max_len);

void simpan_matakuliah_csv(const Matakuliah mk_list[], int count);
void simpan_mahasiswa_csv(const Mahasiswa mhs_list[], int count);
void simpan_krs_csv(const KRS krs_list[], int count);

#endif