#include "workchallenge.h"

int RNG(int min, int max){
    srand(time(NULL));
    int v1 = rand();
    srand(v1);
    return (rand() * v1) % (max - min + 1) + min; // Mengalikan 2 angka random agar hasil bisa merupakan angka besar
}

int countWords(char *filename, char wordlist[WordCount__][6]) {
    int count = 0;
    StartFileWord(filename);
    while (!endOfFile) { // Membaca semua list word
        toupperstr(currentWord.TabWord);
        copyStr(currentWord.TabWord, wordlist[count]);
        ADVFileWordNewLine();
        count++;
    }

    return count;
}

int isWord(char wordlist[WordCount__][6], char word[6], int count){
    int exist = 0;
    int i = 0;
    while (i < count && !exist)
    {
        if (check_strV2(wordlist[i], word))
        {
            exist = 1;
        }
        i++;
    }
    return exist;
}

void randomWord(char wordlist[WordCount__][6], int index, char *result) {
    copyStr(wordlist[index], result);
}

void tebakAngka(TabInt *arruser, int useridx){
    int n = RNG(0, 100);
    //printf("%d\n", n);
    printf("Tebak Angka: ");
    
    int input = 0;
    STARTWORD();
    for (int i = 0; i < currentWord.Length; i++) { // Mengubah string menjadi int
        input = input * 10 + (currentWord.TabWord[i] - '0');
    }
    int i = 1;
    while (input != n && i < 10)
    {
        if (input < n)
        {
            printf("Tebakanmu lebih kecil!\n");
        }

        if (input > n)
        {
            printf("Tebakanmu lebih besar!\n");
        }

        printf("Tebak Angka: ");
    
        STARTWORD();
        input = 0;
        for (int i = 0; i < currentWord.Length; i++) { // Mengubah string menjadi int
            input = input * 10 + (currentWord.TabWord[i] - '0');
        }
        i++;
    }
    if (input == n)
    {
        printf("Tebakanmu benar!\n");
        arruser->TI[useridx].money += 500; // Tambah uang user
        printf("+%d rupiah telah ditambahkan ke akun Anda.(Uang Sekarang = %d)\n", 500, arruser->TI[useridx].money);
    }else{
        printf("Failed\n");
    }
}

void _printPast(char past[6][11], int count){
    int i = 0;
    while (i < count)
    {
        int j = 0;
        while (past[i][j] != '\0')
        {
            if (j != 0 && j % 2 == 0)
            {
                printf(" ");
            }
            
            if (past[i][j] != ' ')
            {
                printf("%c", past[i][j]);
            }
            j++;
        }
        printf("\n");
        i++;
    }    
}

void _printDash(int count){
    int i = 0;
    while (i < 6 - count)
    {
        printf("_ _ _ _ _\n");
        i++;
    }    
}

void wordl3(TabInt *arruser, int useridx){
    char *filename = "../save/word.txt";
    char wordlist[WordCount__][6]; // Menyimpan list kata
    char word[6];
    char past[6][11]; // Menyimpan tebakan sebelumnya
    char input[20];
    int count = 0; // Menandakan berapa try yang digunakan
    int found = 0; // Menandakan berapa huruf yang ditemukan
    int wordnum = countWords(filename, wordlist); // Menghitung ada berapa kata yang mungkin
    randomWord(wordlist, RNG(0, wordnum), word); // Mendapatkan kata jawaban random
    //printf("%s %d %d\n", word, count, found); // Untuk debug
    while (count < 6 && found < 5)
    {
        found = 0;
        int i = 0;
        int aword = 0;
        if (count > 0)
        {
            printf("Hasil:\n");
        }
        _printPast(past, count); // Output tebakan sebelumnya
        _printDash(count); // Menandakan try yang tersisia
        printf("\n");
        while (!aword)
        {
            printf("Masukan Kata Tebakan: ");
            STARTWORD();
            toupperstr(currentWord.TabWord);
            copyStr(currentWord.TabWord, input);
            aword = isWord(wordlist, input, wordnum); // Validasi apakah tebakan merupakan kata
            if (!aword)
            {
                printf("Tebakan Bukan Kata Valid\n");
            }
            
        }

        i = 0;
        while (i < 5)
        {
            if (input[i] == word[i]) // Case ketika posisi huruf benar
            {
                past[count][(i*2)] = input[i];
                past[count][(i*2)+1] = ' ';
                found++;
            }else if(isIn(input[i], word)){ // Case ketika ada huruf pada kata jawaban
                past[count][(i*2)] = input[i];
                past[count][(i*2)+1] = '*';
            }else{ // Case ketika tidak ada huruf pada kata jawaban
                past[count][(i*2)] = input[i];
                past[count][(i*2)+1] = '%';
            }
            i++;   
        }
        past[count][10] = '\0';
        count++;
    }
    printf("Hasil:\n");
    _printPast(past, count); // Output ketika kesempatan sudah habis atau sudah mendapat jawaban
    _printDash(count);
    if (found == 5)
    {
        printf("Menang!!\n");
        arruser->TI[useridx].money += 1500; // Tambah uang user
        printf("+%d rupiah telah ditambahkan ke akun Anda.(Uang Sekarang = %d)\n", 1500, arruser->TI[useridx].money);
    }else{
        printf("Kalah\n");
        printf("Jawaban: %s\n", word);
    }
    
}


void workChallenge(TabInt *arruser, int useridx){
    chal c[chal_count] = {{chal1}, {chal2}};
    printf("Daftar Challenge:\n");
    for (int i = 0; i < chal_count; i++) // Display semua challenge yang ada
    {
        printf("    %d. %s (biaya=%d)\n", i+1, c[i].name, c[i].biaya);
    }
    printf("Masukkan challenge yang dipilih: ");

    char input[50];
    STARTWORD();
    copyStr(currentWord.TabWord, input);
    toupperstr(input);

    int selected = -1;
    int i = 0;
    while (i < chal_count && selected == -1) // Cek challenge apa yang dipilih
    {
        toupperstr(c[i].name);
        if (check_strV2(input, c[i].name))// Cek input kata
        {
            selected = i;
        }
        if (input[0] - '0' - 1 == i) // Cek input angka
        {
            selected = i;
        }
        i++;
    }
    switch (selected)
    {
    case 0: // Case memilih Challenge TebakAngka
        if (arruser->TI[useridx].money < c[selected].biaya) // Cek apakah uang user cukup
        {
            printf("Uang Anda Tidak Cukup (Uang Sekarang = %d)\n", arruser->TI[useridx].money);
            break;
        }
        arruser->TI[useridx].money -= c[selected].biaya; // Kurangi uang user
        printf("Uang Berkurang %d (Uang Sekarang = %d)\n", c[selected].biaya, arruser->TI[useridx].money);
        tebakAngka(arruser, useridx);
        break;
    case 1: // Case memilih Challenge TebakAngka
        if (arruser->TI[useridx].money < c[selected].biaya) // Cek apakah uang user cukup
        {
            printf("Uang Anda Tidak Cukup (Uang Sekarang = %d)\n", arruser->TI[useridx].money);
            break;
        }
        arruser->TI[useridx].money -= c[selected].biaya; // Kurangi uang user
        printf("Uang Berkurang %d (Uang Sekarang = %d)\n", c[selected].biaya, arruser->TI[useridx].money);
        wordl3(arruser, useridx);
        break;
    default:
        printf("Challenge Yang Dipilih Tidak Valid\n");
        break;
    }
}
