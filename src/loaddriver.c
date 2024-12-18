#include <stdio.h>
#include "load.h"

int main() {
    ArrayDin arrayItems;
    TabInt arrayUsers;
    arrayItems = MakeArrayDin();
    MakeEmpty(&arrayUsers);
    boolean SessionStatus;

    printf("Masukkan nama file:\n");
    StartWordNewLine();
    load(currentWord, &arrayItems, &arrayUsers, &SessionStatus);
    
    printf("Daftar Nama Barang dan Harga:\n");
    for(int i = 0; i < Length(arrayItems); i++){
        printf("%d. %s - %d\n", i+1, (Get(arrayItems, i)).name), (Get(arrayItems, i)).price;
    }
    
    printf("Daftar User:\n");
    for (int i = GetFirstIdx(arrayUsers); i <= GetLastIdx(arrayUsers); i++) {
        printf("%d. Uang: %d - Username: %s - Password: %s\n", i+1, (GetElmt(arrayUsers, i)).money, (GetElmt(arrayUsers, i)).name, (GetElmt(arrayUsers, i)).password);
    }

    for(int i = 0; i < NbElmt(arrayUsers); i++){
        printf("Daftar Riwayat Pembelian:\n");
        barang_dibeli currentBarangDibeli;
        
        while(!IsEmptyStack(*(arrayUsers.TI[i].riwayat_pembelian))){
            PopStack(arrayUsers.TI[i].riwayat_pembelian, &currentBarangDibeli);
            printf("Nama barang: %s, Total harga: %d\n", currentBarangDibeli.name, currentBarangDibeli.totalharga);
        }

        printf("Daftar Wishlist:\n");
        nama_barang currentBarangWishlist;

        address currentAddress = First(*(arrayUsers.TI[i].wishlist));
        while(currentAddress != Nuh){
            printf("Nama barang: %s\n", Info(currentAddress));
            currentAddress = currentAddress->next;
        }
    }

    for (int i = 0; i < NbElmt(arrayUsers); i++) {
        User *user = &(arrayUsers.TI[i]);
        free(user->riwayat_pembelian);
        free(user->wishlist);
        free(user->keranjang);
        user->riwayat_pembelian = NULL;
        user->keranjang = NULL;
        user->wishlist = NULL;
    }
}