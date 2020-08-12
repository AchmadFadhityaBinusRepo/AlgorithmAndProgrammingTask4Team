#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// -- Global Variable Declaration --
typedef struct {
    char nama[7];
    char size[8];
    char penyajian[7];
    int harga;
} Minuman;

char *ALLOWED_NAMA[4];
char *ALLOWED_SIZE[3];
char *ALLOWED_PENYAJIAN[3];
Minuman history_transaksi[100];
int total_history_transaksi = 0;

// -- Functions Prototype --
void showMenu();

void aksesMenu(int pilihan);

void inputData();

int hitungHargaMinuman(Minuman minuman);

int isInputValid(char input[], char *pAllowedThings[]);

void masukanKeHistory(Minuman minuman);

void viewHistory();

void deleteHistory();

void deleteHistoryFromArray(int index);

void exitProgram();

void saveToFile();

void readDataMinumanFromFile();

void showDataMinuman();

int main() {
    readDataMinumanFromFile();
    showMenu();
    return 0;
}

void readDataMinumanFromFile() {
    FILE *fp;
    char buff[10];

    fp = fopen("dataminuman.txt", "r");

    for (int i = 0; i < 4; i++) {
        fscanf(fp, "%s\n", buff);
        ALLOWED_NAMA[i] = strdup(buff);
    }

    fscanf(fp, "\n");
    for (int i = 0; i < 3; i++) {
        fscanf(fp, "%s\n", buff);
        ALLOWED_SIZE[i] = strdup(buff);
    }

    fscanf(fp, "\n");
    for (int i = 0; i < 3; i++) {
        fscanf(fp, "%s\n", buff);
        ALLOWED_PENYAJIAN[i] = strdup(buff);
    }
}

void showMenu() {
    int menu_pilihan;
    do {
        printf("\n    Selamat Datang di Aplikasi Pencatatan Transaksi\n"
               "\n"
               "    Menu:\n"
               "    1. Input Data\n"
               "    2. View History Transaksi\n"
               "    3. Delete History Transaksi\n"
               "    4. Exit\n"
               "    \n"
               "    Menu yang anda pilih: ");
        fflush(stdin);
        scanf("%d", &menu_pilihan);
        aksesMenu(menu_pilihan);
    } while (1);
}

void showDataMinuman() {
    printf("\n   Minuman Tersedia\n");
    for (int i = 0; i < 4; i++) {
        printf("   %s\n", ALLOWED_NAMA[i]);
    }

    printf("\n   Ukuran Tersedia\n");
    for (int i = 0; i < 3; i++) {
        printf("   %s\n", ALLOWED_SIZE[i]);
    }

    printf("\n   Penyajian Tersedia\n");
    for (int i = 0; i < 3; i++) {
        printf("   %s\n", ALLOWED_PENYAJIAN[i]);
    }
}

void aksesMenu(int pilihan) {
    switch (pilihan) {
        case 1:
            inputData();
            break;
        case 2:
            viewHistory();
            break;
        case 3:
            deleteHistory();
            break;
        case 4:
            exitProgram();
            break;
        default:
            printf("    Maaf Pilihan menu tidak tersedia!");
            break;
    }
}

void exitProgram() {
    saveToFile();
    exit(1);
}

void saveToFile() {
    FILE *fptr;

    if ((fptr = fopen("history.txt", "w")) == NULL) {
        printf("Eror ketika membuka file");
        return;
    }

    for (int i = 0; i < total_history_transaksi; i++) {
        fprintf(fptr, "  Transaksi ke-%d\n"
                      "    Nama Minuman: %s\n"
                      "    Size: %s\n"
                      "    Penyajian: %s\n"
                      "    Harga: %d\n\n",
                i + 1,
                history_transaksi[i].nama,
                history_transaksi[i].size,
                history_transaksi[i].penyajian,
                history_transaksi[i].harga);
    }
    fclose(fptr);
}

void deleteHistory() {
    int transaksi_yang_akan_dihapus;

    viewHistory();
    do {
        printf("\nTransaksi ke berapa yang akan di hapus? ");
        scanf("%d", &transaksi_yang_akan_dihapus);

        if ((transaksi_yang_akan_dihapus - 1) > total_history_transaksi) {
            printf("\nMaaf transaksi tersebut tidak ada");
        }
    } while ((transaksi_yang_akan_dihapus - 1) > total_history_transaksi);

    deleteHistoryFromArray((transaksi_yang_akan_dihapus - 1));
}

void deleteHistoryFromArray(int index) {
    for (int i = index; i < total_history_transaksi - 1; i++) {
        history_transaksi[i] = history_transaksi[i + 1];
    }
    total_history_transaksi--;
}

void viewHistory() {
    printf("\n    Berikut Data History Transaksi");
    for (int i = 0; i < total_history_transaksi; i++) {
        printf("\n\n  Transaksi ke-%d\n"
               "    Nama Minuman: %s\n"
               "    Size: %s\n"
               "    Penyajian: %s\n"
               "    Harga: %d\n",
               i + 1,
               history_transaksi[i].nama,
               history_transaksi[i].size,
               history_transaksi[i].penyajian,
               history_transaksi[i].harga);
    }
}

void inputData() {
    Minuman minuman;
    char valid;

    showDataMinuman();

    do {
        fflush(stdin);
        printf("\n    Input Nama Minuman: ");
        scanf("%[^\n]%*c", minuman.nama);
    } while (isInputValid(minuman.nama, ALLOWED_NAMA) == 0);

    do {
        fflush(stdin);
        printf("    Input Size Minuman: ");
        scanf("%[^\n]%*c", minuman.size);
    } while (isInputValid(minuman.size, ALLOWED_SIZE) == 0);

    do {
        fflush(stdin);
        printf("    Input Penyajian Minuman: ");
        scanf("%[^\n]%*c", minuman.penyajian);
    } while (isInputValid(minuman.penyajian, ALLOWED_PENYAJIAN) == 0);

    minuman.harga = hitungHargaMinuman(minuman);

    printf("\n    Nama Minuman: %s\n"
           "    Size: %s\n"
           "    Penyajian: %s\n"
           "    Harga: %d", minuman.nama, minuman.size, minuman.penyajian, minuman.harga);

    printf("\n\n  Apakah data di atas sudah valid?(y/n)");
    scanf("%c", &valid);

    if (valid == 'n') {
        return;
    } else if (valid == 'y') {
        masukanKeHistory(minuman);
    }
}

void masukanKeHistory(Minuman minuman) {
    history_transaksi[total_history_transaksi] = minuman;
    total_history_transaksi++;
}

int isInputValid(char input[], char *pAllowedThings[]) {
    for (int i = 0; i < 4; i++) {
        if (strcmp(input, pAllowedThings[i]) == 0) {
            return 1;
        }
    }
    printf("\n    Maaf input tidak valid\n");
    return 0;
}

int hitungHargaMinuman(Minuman minuman) {
    int panjang_karakter_nama = strlen(minuman.nama);
    int panjang_karakter_size = strlen(minuman.size);
    int panjang_karakter_penyajian = strlen(minuman.penyajian);
    return panjang_karakter_size * panjang_karakter_nama * panjang_karakter_penyajian * 100;
}
