#include "cart.h"

void cartadd(TabInt *arrayUsers, int useridx, ArrayDin arrayItems, Barang barang, int quantity) {
    boolean found = false;
    for (int i=0 ; i<arrayItems.Neff ; i++) {
        Barang curr = Get(arrayItems, i);
        if (check_strV2(curr.name, barang.name)) {
            found = true;
        }
    }
    if (!found) {
        printf("Barang tidak ada di toko!\n");
    } else {
        if (quantity == 0) {
            printf("Jumlah barang yang dimasukkan ke dalam cart tidak bisa 0!\n");
        } else if (quantity < 0) {
            printf("Barang yang dimasukkan ke dalam keranjang harus berjumlah positif!\n");
        } else {
            InsertMap(arrayUsers->TI[useridx].keranjang, barang.name, quantity);

            printf("Berhasil menambahkan %d %s ke keranjang belanja!\n", quantity, barang.name);
        }
    }
}

void cartpay(TabInt *arrayUsers, int useridx, ArrayDin arrayItems) {
    if (IsEmptyMap(*arrayUsers->TI[useridx].keranjang)) {
        printf("Keranjang kamu kosong!\n");
    } else {
        printf("Kamu akan membeli barang-barang berikut:\n");
        printf("Kuantitas\t| Nama\t\t| Total\n");
        int totalPrice = 0;
        for (int i=0 ; i< arrayUsers->TI[useridx].keranjang->Count ; i++) {
            boolean found = false;
            int idxBarang;
            for (int j=0 ; j<arrayItems.Neff; j++) {
                if (compareStrings(arrayUsers->TI[useridx].keranjang->Elements[i].Key, arrayItems.A[j].name) == 0) {
                    found = true;
                    idxBarang = j;
                    break;
                }
            }
            int harga = ((arrayUsers->TI[useridx].keranjang->Elements[i].Value)*arrayItems.A[idxBarang].price);
            printf("%d\t\t| %s\t\t| %d\n", arrayUsers->TI[useridx].keranjang->Elements[i].Value, arrayUsers->TI[useridx].keranjang->Elements[i].Key, harga);
            totalPrice += harga;
        }
        printf("Total biaya yang harus dikeluarkan adalah %d, apakah jadi dibeli? (Ya/Tidak): ", totalPrice);
        STARTFRASA();
        if (check_strV2(CurrentFrasa.TabWord, "Ya")) {
            if (arrayUsers->TI[useridx].money < totalPrice) {
                printf("Uang kamu hanya %d, tidak cukup untuk membeli keranjang!\n", arrayUsers->TI[useridx].money);
            } else {
                int maxprice = -1;
                barang_dibeli maxitem;
                boolean found = false;
                int idxBarang;
                for (int i=0 ; i < arrayUsers->TI[useridx].keranjang->Count ; i++) {
                    for (int j=0 ; j<arrayItems.Neff; j++) {
                        if (compareStrings(arrayUsers->TI[useridx].keranjang->Elements[i].Key, arrayItems.A[j].name) == 0) {
                            found = true;
                            idxBarang = j;
                            break;
                        }
                    }
                    int harga = ((arrayUsers->TI[useridx].keranjang->Elements[i].Value)*arrayItems.A[idxBarang].price);
                    if (arrayUsers->TI[useridx].keranjang->Elements[i].Value > maxprice) {
                        copyStringMap(maxitem.name, arrayUsers->TI[useridx].keranjang->Elements[i].Key);
                        maxitem.totalharga = harga;
                        maxprice = harga;
                    }
                }
                PushStack(arrayUsers->TI[useridx].riwayat_pembelian, maxitem); // Push barang dengan total harga paling mahal saja
                arrayUsers->TI[useridx].money = arrayUsers->TI[useridx].money - totalPrice;

                for (int i=0 ; i<=arrayUsers->TI[useridx].keranjang->Count ; i++) {
                    DeleteMap(arrayUsers->TI[useridx].keranjang, arrayUsers->TI[useridx].keranjang->Elements[i].Key, arrayUsers->TI[useridx].keranjang->Elements[i].Value);
                }

                printf("\n");
                printf("Selamat kamu telah membeli barang-barang tersebut!\n");
            }
        } else if (check_strV2(CurrentFrasa.TabWord, "Tidak")) {
        } else {
            printf("Input yang anda masukkan tidak valid!\n");
        }
    }
}

void cartremove(TabInt *arrayUsers, int useridx, Barang barang, int quantity) {
    boolean found = false;
    for (int i=0; i<arrayUsers->TI[useridx].keranjang->Count; i++) {
        if (check_str(arrayUsers->TI[useridx].keranjang->Elements[i].Key, barang.name)) {
            found = true;
        }
    }
    if (!found) {
        printf("Barang tidak ada di keranjang belanja!\n");
    } else {
        if (quantity <= 0) {
            printf("Tidak berhasil mengurangi, masukan angka harus positif!\n");
        } else if (quantity > ValueMap(*arrayUsers->TI[useridx].keranjang, barang.name)) {
            printf("Tidak berhasil mengurangi, hanya terdapat %d %s pada keranjang!\n", ValueMap(*arrayUsers->TI[useridx].keranjang, barang.name), barang.name);
        } else {
            DeleteMap(arrayUsers->TI[useridx].keranjang, barang.name, quantity);
            printf("Berhasil mengurangi %d %s dari keranjang belanja!\n", quantity, barang.name);
        }
    }
}

void cartshow(TabInt *arrayUsers, int useridx, ArrayDin arrayItems) {
    if (IsEmptyMap(*arrayUsers->TI[useridx].keranjang)) {
        printf("Keranjang kamu kosong!\n");
    } else {
        printf("Berikut adalah isi keranjang belanjamu!\n");
        printf("Kuantitas\t| Nama\t\t| Total\n");
        int totalPrice = 0;
        for (int i=0 ; i<arrayUsers->TI[useridx].keranjang->Count ; i++) {
            boolean found = false;
            int idxBarang;
            for (int j=0 ; j<arrayItems.Neff; j++) {
                if (compareStrings(arrayUsers->TI[useridx].keranjang->Elements[i].Key, arrayItems.A[j].name) == 0) {
                    found = true;
                    idxBarang = j;
                    break;
                }
            }
            int harga = ((arrayUsers->TI[useridx].keranjang->Elements[i].Value)*arrayItems.A[idxBarang].price);
            printf("%d\t\t| %s\t\t| %d\n", arrayUsers->TI[useridx].keranjang->Elements[i].Value, arrayUsers->TI[useridx].keranjang->Elements[i].Key, harga);
            totalPrice += harga;
        }
        printf("Total biaya yang harus dikeluarkan adalah %d.\n", totalPrice);
    }
}

void cartfunction(TabInt *arrayUsers, int useridx, ArrayDin arrayItems, char arg[]) {
    removeFirstnString(arg, 5);
    if (check_str(arg, "ADD\0")) {
        Barang barang;
        removeFirstnString(arg, 4);
        char arg2[100];
        copyStr2(arg2, arg);
        removeLastWord(arg);
        copyStr2(barang.name, arg);
        keepLastWord(arg2);
        int quantity = stringToInteger(arg2);
        cartadd(arrayUsers, useridx, arrayItems, barang, quantity);
    } else if (check_str(arg, "REMOVE\0")) {
        Barang barang;
        removeFirstnString(arg, 7);
        char arg2[100];
        copyStr2(arg2, arg);
        removeLastWord(arg);
        copyStr2(barang.name, arg);
        keepLastWord(arg2);
        int quantity = stringToInteger(arg2);
        cartremove(arrayUsers, useridx, barang, quantity);
    } else if (check_strV2(arg, "SHOW\0")) {
        cartshow(arrayUsers, useridx, arrayItems);
    } else if (check_strV2(arg, "PAY\0")) {
        cartpay(arrayUsers, useridx, arrayItems);
    } else {
        printf("Perintah yang anda masukkan tidak valid!\n");
    }
}