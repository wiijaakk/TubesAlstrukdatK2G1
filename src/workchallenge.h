#ifndef __WORKCHALLENGE_H__
#define __WORKCHALLENGE_H__

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "str.h"
#include "ADT.h"

#define WordCount__ 14900
#define chal_count 2
//List Chal
//             Name             Biaya
#define chal1 "TebakAngka",    200
#define chal2 "WORDL399",         500

typedef struct {
  char name[50];
  int biaya;
} chal;

void workChallenge(TabInt *arruser ,int useridx);

#endif