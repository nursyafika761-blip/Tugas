#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> 
#include "filedata.h"

// ===========================================
// FUNGSI UTILITY (Cari MHS)
// ===========================================

// Konstanta yang diperlukan
#define FILENAME_MHS "mahasiswa.csv"
#define FILENAME_KRS "krs.csv"
// Fungsi untuk membaca dan mencari Mahasiswa berdasarkan NIM dari mahasiswa.csv
bool cari_mahasiswa_dari_csv(const char *nim_dicari, Mahasiswa *hasil) {
    FILE *file = fopen(FILENAME_MHS, "r");
    if (file == NULL) return false;

    char line[256];
    // Skip header
    if (fgets(line, sizeof(line), file) == NULL) {
        fclose(file);
        return false;
    }
    
    while (fgets(line, sizeof(line), file)) {
        char temp_line[256];
        strcpy(temp_line, line);
        
        char *token = strtok(temp_line, ",");
        
        if (token && strcmp(token, nim_dicari) == 0) {
            strcpy(hasil->nim, token);
            
            // Nama
            token = strtok(NULL, ","); 
            if (token) {
                if (token[0] == '"' && token[strlen(token) - 1] == '"') {
                    token[strlen(token) - 1] = '\0'; 
                    strcpy(hasil->nama, token + 1);
                } else {
                    strcpy(hasil->nama, token);
                }
            }
            
            // Prodi
            token = strtok(NULL, ",");
            if (token) {
                if (token[0] == '"' && token[strlen(token) - 1] == '"') {
                    token[strlen(token) - 1] = '\0'; 
                    strcpy(hasil->prodi, token + 1);
                } else {
                    strcpy(hasil->prodi, token);
                }
            }
            
            // IPK
            token = strtok(NULL, "\n");
            if (token) hasil->ipk = atof(token);
            
            fclose(file);
            return true;
        }
    }
    fclose(file);
    return false;
}

// ===========================================
// FUNGSI TAMPILAN RINGKASAN KRS (KODE MK SAJA - FORMAT SESUAI)
// ===========================================

void tampilkan_ringkasan_krs(const Mahasiswa *mhs_data) {
    printf("\n=============================\n");
    printf("  === RINGKASAN KRS ===\n");
    printf("=============================\n");
    
    // FORMATTING OUTPUT DISINI DIPASTIKAN SAMA PERSIS DENGAN CONTOH ANDA
    printf("NIM : %s\n", mhs_data->nim);  // NIM (Spasi sebelum ':')
    printf("Nama: %s\n", mhs_data->nama);  // Nama (TANPA Spasi sebelum ':')
    printf("Prodi: %s\n", mhs_data->prodi); // Prodi (TANPA Spasi sebelum ':')
    printf("IPK : %.2f\n", mhs_data->ipk);  // IPK (Spasi sebelum ':')
    
    printf("Mata kuliah yang diambil:\n"); // Kalimat pengantar

    FILE *file = fopen(FILENAME_KRS, "r");
    if (file == NULL) {
        printf("Error: File KRS belum ada.\n");
        return;
    }

    char line[256];
    // Skip header
    if (fgets(line, sizeof(line), file) == NULL) {
        fclose(file);
        return;
    }

    bool ada_krs = false;
    while (fgets(line, sizeof(line), file)) {
        char temp_nim[15];
        char temp_kode_mk[10];

        char temp_line[256];
        strcpy(temp_line, line);
        
        char *token = strtok(temp_line, ",");
        if (token) strcpy(temp_nim, token);

        token = strtok(NULL, "\n");
        if (token) strcpy(temp_kode_mk, token);

        // Cek apakah NIM sesuai
        if (strcmp(temp_nim, mhs_data->nim) == 0) {
            printf("- %s\n", temp_kode_mk); // Cetak dash '-' diikuti kode MK
            ada_krs = true;
        }
    }
    
    if (!ada_krs) {
         printf("(Belum ada Mata Kuliah yang diambil di sesi ini)\n");
    }

    fclose(file);
    printf("=============================\n");
}


// ===========================================
// FUNGSI UTAMA UNTUK MODUL 3
// ===========================================

void eksekusi_modul_krs_dengan_ringkasan() {
    char nim_input[15];
    Mahasiswa mhs_ditemukan = {"", "", "", 0.0};
    
    printf("\n--- MAIN.EXE 3: Input & Ringkasan KRS ---\n");
    printf("Masukkan NIM Mahasiswa yang akan mengambil KRS: ");
    scanf("%s", nim_input);
    clear_input_buffer();

    if (cari_mahasiswa_dari_csv(nim_input, &mhs_ditemukan)) {
        printf("Mahasiswa Ditemukan: %s (%s)\n", mhs_ditemukan.nama, mhs_ditemukan.nim);
        
        jalankan_modul_krs(&mhs_ditemukan);
        
        tampilkan_ringkasan_krs(&mhs_ditemukan);

    } else {
        printf("Error: Mahasiswa dengan NIM %s tidak ditemukan di %s.\n", nim_input, FILENAME_MHS);
        printf("Silakan jalankan MAIN.EXE 2 terlebih dahulu untuk input data Mahasiswa.\n");
    }
}


// ===========================================
// FUNGSI UTAMA PROGRAM (MENU)
// ===========================================

void tampilkan_menu() {
    printf("\n========================================\n");
    printf("  Sistem Informasi Akademik Modular\n");
    printf("========================================\n");
    printf("Pilih Eksekusi (main.exe) yang akan dijalankan:\n");
    printf("1. Menjalankan modul input MK (main.exe 1)\n");
    printf("2. Menjalankan modul input MHS (main.exe 2)\n");
    printf("3. Menjalankan modul input KRS & Ringkasan (main.exe 3)\n");
    printf("4. Keluar\n");
    printf("----------------------------------------\n");
    printf("Masukkan pilihan (1-4): ");
}

int main() {
    int pilihan;

    do {
        tampilkan_menu();
        if (scanf("%d", &pilihan) != 1) {
            clear_input_buffer(); 
            pilihan = 0; 
        } else {
            clear_input_buffer();
        }

        switch (pilihan) {
            case 1:
                jalankan_modul_mk();
                break;
            case 2:
                jalankan_modul_mhs();
                break;
            case 3:
                eksekusi_modul_krs_dengan_ringkasan();
                break;
            case 4:
                printf("\nProgram diakhiri. Sampai jumpa!\n");
                break;
            default:
                printf("\nPilihan tidak valid. Silakan coba lagi.\n");
        }
    } while (pilihan != 4);

    return 0;
}
