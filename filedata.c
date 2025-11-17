#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef filedata_h
#include "filedata.h"
#endif


void bersihkanBufferInput() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void bacaDariFileCSV(const char *namaFile) {
    FILE *fp = fopen(namaFile, "r");
    if (!fp) {
        fprintf(stderr, "Gagal membaca file '%s'. File mungkin belum ada.\n", namaFile);
        return;
    }

    char baris[256];
    printf("\n=== Data dari File '%s' ===\n", namaFile);
    while (fgets(baris, sizeof(baris), fp)) {
        printf("%s", baris); 
    }
    fclose(fp);
}

Matakuliah* inputDataMatakuliah(int *jumlah) {
    printf("Masukkan jumlah matakuliah: ");
    scanf("%d", jumlah);
    bersihkanBufferInput();

    Matakuliah *data = (Matakuliah*) malloc((*jumlah) * sizeof(Matakuliah));
    if (!data) {
        printf("Alokasi memori gagal!\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < *jumlah; i++) {
        printf("\nMatakuliah #%d\n", i + 1);
        
        printf("ID MK  : ");
        fgets(data[i].id_mk, MAX_MK_ID_LEN, stdin);
        data[i].id_mk[strcspn(data[i].id_mk, "\n")] = '\0'; 

        printf("Nama   : ");
        fgets(data[i].nama, MAX_NAME_LEN, stdin);
        data[i].nama[strcspn(data[i].nama, "\n")] = '\0'; 

        printf("SKS    : ");
        scanf("%d", &data[i].sks);
        bersihkanBufferInput();
    }
    return data;
}

void simpanMatakuliahKeCSV(Matakuliah *mk, int jumlah) {
    FILE *fp = fopen("matakuliah.csv", "w"); 
    if (!fp) {
        printf("Gagal membuka file matakuliah.csv untuk menulis!\n");
        return;
    }

    fprintf(fp, "ID_MK,Nama,SKS\n"); 
    for (int i = 0; i < jumlah; i++) {
        fprintf(fp, "%s,%s,%d\n",
                mk[i].id_mk, mk[i].nama, mk[i].sks);
    }

    fclose(fp);
    printf("\nData berhasil disimpan ke file 'matakuliah.csv'\n");
}

Mahasiswa* inputDataMahasiswa(int *jumlah) {
    printf("Masukkan jumlah mahasiswa: ");
    scanf("%d", jumlah);
    bersihkanBufferInput();

    Mahasiswa *data = (Mahasiswa*) malloc((*jumlah) * sizeof(Mahasiswa));
    if (!data) {
        printf("Alokasi memori gagal!\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < *jumlah; i++) {
        printf("\nMahasiswa #%d\n", i + 1);
        data[i].id = i + 1; 

        printf("Nama   : ");
        fgets(data[i].nama, MAX_NAME_LEN, stdin);
        data[i].nama[strcspn(data[i].nama, "\n")] = '\0';

        printf("Prodi  : ");
        fgets(data[i].prodi, MAX_PRODI_LEN, stdin);
        data[i].prodi[strcspn(data[i].prodi, "\n")] = '\0';

        printf("IPK    : ");
        scanf("%f", &data[i].ipk);
        bersihkanBufferInput();
    }
    return data;
}

void simpanMahasiswaKeCSV(Mahasiswa *mhs, int jumlah) {
    FILE *fp = fopen("mahasiswa.csv", "w");
    if (!fp) {
        printf("Gagal membuka file mahasiswa.csv untuk menulis!\n");
        return;
    }

    fprintf(fp, "ID,Nama,Prodi,IPK\n");
    for (int i = 0; i < jumlah; i++) {
        fprintf(fp, "%d,%s,%s,%.2f\n",
                mhs[i].id, mhs[i].nama, mhs[i].prodi, mhs[i].ipk);
    }

    fclose(fp);
    printf("\nData berhasil disimpan ke file 'mahasiswa.csv'\n");
}

KRS* inputDataKRS(int *jumlah) {
    printf("Masukkan jumlah entri KRS: ");
    scanf("%d", jumlah);
    bersihkanBufferInput();

    KRS *data = (KRS*) malloc((*jumlah) * sizeof(KRS));
    if (!data) {
        printf("Alokasi memori gagal!\n");
        exit(EXIT_FAILURE);
    }

    printf("\nInput Data KRS (Pasangan ID Mahasiswa dan ID Matakuliah)\n");
    for (int i = 0; i < *jumlah; i++) {
        printf("\nEntri #%d\n", i + 1);
        
        printf("ID Mahasiswa   : ");
        scanf("%d", &data[i].id_mahasiswa);
        bersihkanBufferInput();

        printf("ID Matakuliah  : ");
        fgets(data[i].id_matakuliah, MAX_MK_ID_LEN, stdin);
        data[i].id_matakuliah[strcspn(data[i].id_matakuliah, "\n")] = '\0';
    }
    return data;
}

void simpanKRSKeCSV(KRS *krs, int jumlah) {
    FILE *fp = fopen("krs.csv", "w"); 
    if (!fp) {
        printf("Gagal membuka file krs.csv untuk menulis!\n");
        return;
    }

    fprintf(fp, "ID_Mahasiswa,ID_Matakuliah\n"); 
    for (int i = 0; i < jumlah; i++) {
        fprintf(fp, "%d,%s\n",
                krs[i].id_mahasiswa, krs[i].id_matakuliah);
    }

    fclose(fp);
    printf("\nData berhasil disimpan ke file 'krs.csv'\n");
}