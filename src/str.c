#include "str.h"

void copyStr(char *in, char *out) {
    int i = 0;
    while (in[i] != '\0') {
        out[i] = in[i];
        i++;
    }
    out[i] = '\0';
}

int isIn(char c, char* s){
    int i = 0;
    int found = 0;
    while (s[i] != '\0' && !found)
    {
        if (c == s[i])
        {
            found = 1;
        }
        i++;
    }
    return found;
}

int check_str(char str1[], char str2[]){
    int check = 1;
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0' && check)
    {
        if (str1[i] != str2[i])
        {
            check = 0;
        }
        i++;
    }
    return check;    
}

int check_strV2(char str1[], char str2[]){
    int check = 1;
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0' && check)
    {
        if (str1[i] != str2[i])
        {
            check = 0;
        }
        i++;
    }
    if (str1[i] != '\0' || str2[i] != '\0')
    {
        check = 0;
    }
    
    return check;    
}

void toupperstr(char str[]) {
    int i = 0;
    while (str[i] != '\0') {
        if (str[i] >= 'a' && str[i] <= 'z') {
            str[i] = str[i] - 'a' + 'A';
        }
        i++;
    }
}

void removeFirstnString(char str[], int offset){
    int i = 0;
    while (str[i+offset] != '\0')
    {
        str[i] = str[i+offset];
        i++;
    }
    str[i] = '\0';
}