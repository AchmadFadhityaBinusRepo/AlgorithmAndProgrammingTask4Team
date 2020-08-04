#include <stdio.h>
#include <string.h>

typedef struct {
    char nama[7];
    char size[8];
    char penyajian[7];
    int harga;
} Minuman;

const char *ALLOWED_NAMA[] = {"teh", "coklat", "soda", "kopi"};
const char *ALLOWED_SIZE[] = {"small", "medium", "largest"};
const char *ALLOWED_PENYAJIAN[] = {"dingin", "panas", "hangat"};
Minuman history_transaksi[100];
int total_history_transaksi = 0;

void showMenu();

void aksesMenu(int pilihan);

void inputData();

int hitungHargaMinuman(Minuman minuman);

int isInputValid(char input[7], const char *pAllowedThings[3]);


void masukanKeHistory(Minuman minuman);

void viewHistory();

void deleteHistory();

void deleteHistoryFromArray(int index);

int main() {
    showMenu();
    return 0;
}

void showMenu() {
    int menu_pilihan;
    do {
        printf("    Selamat Datang di Aplikasi Pencatatan Transaksi\n"
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
//            exitProgram();
            break;
        default:
            printf("    Maaf Pilihan menu tidak tersedia!");
            break;
    }
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
    printf("\nBerikut Data History Transaksi");
    for (int i = 0; i < total_history_transaksi; i++) {
        printf("\nTransaksi ke-%d\n"
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

    do {
        fflush(stdin);
        printf("Input Nama Minuman: ");
        scanf("%[^\n]%*c", minuman.nama);
    } while (isInputValid(minuman.nama, ALLOWED_NAMA) == 0);

    do {
        fflush(stdin);
        printf("Input Size Minuman: ");
        scanf("%[^\n]%*c", minuman.size);
    } while (isInputValid(minuman.size, ALLOWED_SIZE) == 0);

    do {
        fflush(stdin);
        printf("Input Penyajian Minuman: ");
        scanf("%[^\n]%*c", minuman.penyajian);
    } while (isInputValid(minuman.penyajian, ALLOWED_PENYAJIAN) == 0);

    minuman.harga = hitungHargaMinuman(minuman);

    printf("\n    Nama Minuman: %s\n"
           "    Size: %s\n"
           "    Penyajian: %s\n"
           "    Harga: %d", minuman.nama, minuman.size, minuman.penyajian, minuman.harga);

    printf("   \nApakah data di atas sudah valid? ");
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

int isInputValid(char input[], const char *pAllowedThings[]) {
    for (int i = 0; i < 4; i++) {
        if (strcmp(input, pAllowedThings[i]) == 0) {
            return 1;
        }
    }
    printf("\nMaaf input tidak valid\n");
    return 0;
}

int hitungHargaMinuman(Minuman minuman) {
    int panjang_karakter_nama = strlen(minuman.nama);
    int panjang_karakter_size = strlen(minuman.size);
    int panjang_karakter_penyajian = strlen(minuman.penyajian);
    return panjang_karakter_size * panjang_karakter_nama * panjang_karakter_penyajian * 100;
}
