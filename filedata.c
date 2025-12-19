#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filedata.h"

// --- Konstanta yang diperlukan ---
#define FILENAME_MK "matakuliah.csv"
#define FILENAME_MHS "mahasiswa.csv"
#define FILENAME_KRS "krs.csv"
#define MAX_STR_LEN 100
#define MAX_MHS 100
#define MAX_KRS 100

// --- Utility Functions ---

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void get_string_input(char *dest, int max_len) {
    fgets(dest, max_len, stdin);
    dest[strcspn(dest, "\n")] = 0;
}

// --- Fungsi Simpan CSV ---

void simpan_matakuliah_csv(const Matakuliah mk_list[], int count) {
    FILE *file = fopen(FILENAME_MK, "w");
    if (file == NULL) {
        perror("Gagal membuka file matakuliah.csv");
        return;
    }
    fprintf(file, "Kode,Nama,SKS\n");
    for (int i = 0; i < count; i++) {
        fprintf(file, "%s,\"%s\",%d\n", mk_list[i].kode, mk_list[i].nama, mk_list[i].sks);
    }
    fclose(file);
    printf("\n✅ Data Matakuliah berhasil disimpan ke %s\n", FILENAME_MK);
}

void simpan_mahasiswa_csv(const Mahasiswa mhs_list[], int count) {
    FILE *file = fopen(FILENAME_MHS, "w");
    if (file == NULL) {
        perror("Gagal membuka file mahasiswa.csv");
        return;
    }
    fprintf(file, "NIM,Nama,Prodi,IPK\n");
    for (int i = 0; i < count; i++) {
        // Asumsi IPK diinput dalam Modul MHS
        fprintf(file, "%s,\"%s\",\"%s\",%.2f\n", mhs_list[i].nim, mhs_list[i].nama, mhs_list[i].prodi, mhs_list[i].ipk);
    }
    fclose(file);
    printf("\n✅ Data Mahasiswa berhasil disimpan ke %s\n", FILENAME_MHS);
}

// PERHATIKAN: Output KRS HANYA NIM dan KODE_MK (Sesuai Perintah Dosen)
void simpan_krs_csv(const KRS krs_list[], int count) {
    FILE *file = fopen(FILENAME_KRS, "w");
    if (file == NULL) {
        perror("Gagal membuka file krs.csv");
        return;
    }
    fprintf(file, "NIM,Kode_MK\n"); // Hanya dua kolom
    for (int i = 0; i < count; i++) {
        fprintf(file, "%s,%s\n", krs_list[i].nim_mhs, krs_list[i].kode_mk);
    }
    fclose(file);
    printf("\n✅ Data KRS berhasil disimpan ke %s\n", FILENAME_KRS);
}


// --- Implementasi Modul 1: Matakuliah ---
void jalankan_modul_mk() {
    Matakuliah daftar_mk[MAX_MATKUL];
    int jumlah_mk = 0;
    char pilihan[5];

    printf("\n--- MAIN.EXE 1: Input Matakuliah ---\n");
    do {
        if (jumlah_mk < MAX_MATKUL) {
            printf("\n--- Input MK ke-%d ---\n", jumlah_mk + 1);
            printf("Masukkan Kode MK: ");
            scanf("%s", daftar_mk[jumlah_mk].kode);
            clear_input_buffer();

            printf("Masukkan Nama MK: ");
            get_string_input(daftar_mk[jumlah_mk].nama, MAX_STR_LEN); 
            
            printf("Masukkan Jumlah SKS: ");
            if (scanf("%d", &daftar_mk[jumlah_mk].sks) != 1) {
                printf("Input SKS tidak valid. Dibatalkan.\n");
                clear_input_buffer();
                continue;
            }
            clear_input_buffer(); 
            
            jumlah_mk++;
            printf("-> Matakuliah berhasil ditambahkan!\n");
        } else {
            break;
        }

        printf("Mau input Matakuliah lagi? (y/t): ");
        get_string_input(pilihan, 5);
        
    } while (pilihan[0] == 'y' || pilihan[0] == 'Y');

    if (jumlah_mk > 0) {
        simpan_matakuliah_csv(daftar_mk, jumlah_mk);
    }
}

// --- Implementasi Modul 2: Mahasiswa ---
void jalankan_modul_mhs() {
    Mahasiswa daftar_mhs[MAX_MHS];
    int jumlah_mhs = 0;
    char pilihan[5];

    printf("\n--- MAIN.EXE 2: Input Mahasiswa ---\n");
    do {
        if (jumlah_mhs < MAX_MHS) {
            printf("\n--- Input MHS ke-%d ---\n", jumlah_mhs + 1);
            
            printf("Masukkan NIM: ");
            scanf("%s", daftar_mhs[jumlah_mhs].nim);
            clear_input_buffer();

            printf("Masukkan Nama Mahasiswa: ");
            get_string_input(daftar_mhs[jumlah_mhs].nama, MAX_STR_LEN);

            printf("Masukkan Prodi: ");
            get_string_input(daftar_mhs[jumlah_mhs].prodi, MAX_STR_LEN);
            
            printf("Masukkan IPK (contoh: 3.45): ");
            if (scanf("%f", &daftar_mhs[jumlah_mhs].ipk) != 1) {
                printf("Input IPK tidak valid. Dibatalkan.\n");
                clear_input_buffer();
                continue;
            }
            clear_input_buffer();

            jumlah_mhs++;
            printf("-> Mahasiswa berhasil ditambahkan!\n");
        } else {
            break;
        }

        printf("Mau input Mahasiswa lagi? (y/t): ");
        get_string_input(pilihan, 5);
        
    } while (pilihan[0] == 'y' || pilihan[0] == 'Y');

    if (jumlah_mhs > 0) {
        simpan_mahasiswa_csv(daftar_mhs, jumlah_mhs);
    }
}

// --- Implementasi Modul 3: KRS ---
// Fungsi ini HANYA bertanggung jawab untuk input KRS dan menyimpan ke krs.csv
void jalankan_modul_krs(const Mahasiswa *mhs_terpilih) {
    KRS daftar_krs[MAX_KRS];
    int jumlah_krs = 0;
    char pilihan[5];
    
    // Gunakan NIM mahasiswa yang sudah dicari di main.c
    if (mhs_terpilih == NULL) {
        printf("Error: Data Mahasiswa tidak ditemukan atau belum dicari.\n");
        return;
    }

    printf("\n--- MAIN.EXE 3: Input KRS untuk %s ---\n", mhs_terpilih->nama);
    do {
        if (jumlah_krs < MAX_KRS) {
            printf("\n--- Input KRS ke-%d ---\n", jumlah_krs + 1);
            
            // Set NIM secara otomatis dari Mahasiswa yang dicari
            strcpy(daftar_krs[jumlah_krs].nim_mhs, mhs_terpilih->nim);

            printf("Masukkan Kode Matakuliah yang dipilih: ");
            scanf("%s", daftar_krs[jumlah_krs].kode_mk);
            clear_input_buffer();

            // Semester hanya diinput tapi TIDAK disimpan di CSV (krs.csv)
            printf("Masukkan Semester (contoh: Ganjil 2024): ");
            get_string_input(daftar_krs[jumlah_krs].semester, MAX_STR_LEN);
            
            jumlah_krs++;
            printf("-> Matakuliah berhasil ditambahkan ke KRS!\n");
        } else {
            break;
        }

        printf("Mau input Matakuliah lain untuk KRS? (y/t): ");
        get_string_input(pilihan, 5);
        
    } while (pilihan[0] == 'y' || pilihan[0] == 'Y');

    if (jumlah_krs > 0) {
        simpan_krs_csv(daftar_krs, jumlah_krs);
    }
}