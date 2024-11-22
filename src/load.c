#include <stdio.h>
#include <stdlib.h>
#include "load.h"

void load(Word filename, ArrayDin* arrayItems, TabInt* arrayUsers) {
    int total = 0;
    Barang currentBarang;
    User currentUser;
    boolean exists;

    char filenameStr[50];
    for (int i = 0; i < filename.Length; i++) {
        filenameStr[i] = filename.TabWord[i];
    }
    filenameStr[filename.Length] = '\0';

    if (isFileValid(filenameStr)) {   
        // Membuka file
        StartFileWord(filenameStr);

        // Membaca total barang yang tersimpan dalam file
        total = wordToInt(currentWord);

        // Memasukkan informasi barang ke arrayItems
        for (int i = 0; i < total; i++) {
            ADVFileWordSpace();
            currentBarang.price = wordToInt(currentWord);

            ADVFileWordNewLine();
            for (int j = 0; j < currentWord.Length; j++) {
                currentBarang.name[j] = currentWord.TabWord[j];
            }
            currentBarang.name[currentWord.Length] = '\0';

            InsertLast(arrayItems, currentBarang);
        }

        // Membaca total user yang tersimpan dalam file
        ADVFileWordNewLine();
        total = wordToInt(currentWord);

        // Memasukkan informasi user ke arrayUsers
        for (int i = 0; i < total; i++) {
            ADVFileWordSpace();
            currentUser.money = wordToInt(currentWord);
            
            ADVFileWordSpace();
            for (int j = 0; j < currentWord.Length; j++) {
                currentUser.name[j] = currentWord.TabWord[j];
            }
            currentUser.name[currentWord.Length] = '\0';

            ADVFileWordNewLine();
            for (int j = 0; j < currentWord.Length; j++) {
                currentUser.password[j] = currentWord.TabWord[j];
            }
            currentUser.password[currentWord.Length] = '\0';

            SetEl(arrayUsers, i + 1, currentUser);
        }

        if (Length(*arrayItems) == 0 || NbElmt(*arrayUsers) == 0) {
            printf("File tidak memuat data yang sesuai. PURRMART gagal dijalankan.\n");
        }
        else {
            printf("Save file berhasil dibaca. PURRMART berhasil dijalankan.\n");
        }
    }
    else {
        printf("Save file tidak ditemukan. PURRMART gagal dijalankan.\n");
    }
}