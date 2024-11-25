#include <stdio.h>
#include "load.h"

void printBarang(Barang b) {
    printf("Harga: %d, Nama: %s\n", b.price, b.name);
}

void printUser(User u) {
    printf("Uang: %d, Username: %s, Password: %s\n", u.money, u.name, u.password);
}

int main() {
    ArrayDin arrayItems;
    TabInt arrayUsers;
    arrayItems = MakeArrayDin();
    boolean SessionStatus;
    MakeEmpty(&arrayUsers);
    
    printf("Masukkan command: ");
    StartWordSpace();

    if (compareWordToString(currentWord, "LOAD")) {
        ADVWordNewLine();
        load(currentWord, &arrayItems, &arrayUsers, SessionStatus);
        
        if (isFileValid && Length(arrayItems) > 0 && NbElmt(arrayUsers) > 0) {
            printf("Daftar Barang:\n");
            for (int i = 0; i < Length(arrayItems); i++) {
                printf("Barang %d - ", i+1);
                printBarang(Get(arrayItems, i));
            }
            
            printf("Daftar User:\n");
            for (int i = GetFirstIdx(arrayUsers); i <= GetLastIdx(arrayUsers); i++) {
                printf("User %d - ", i);
                printUser(GetElmt(arrayUsers, i));
            }
        }
    }
}