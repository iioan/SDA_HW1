/* TEODORESCU Ioan - 313CB*/
#include <stdlib.h>

#include <stdio.h>

#include <string.h>

#include <stdarg.h>

#include <time.h>

#include "tlg.h"

#ifndef _TAB_HASH_
#define _TAB_HASH_

typedef int( * TFElem)(void * ); /* functie prelucrare element */
typedef int( * TFCmp)(void * , void * ); /* functie de comparare doua elemente */
typedef void( * TF)(void * ); /* functie afisare/eliberare un element */
typedef int( * TFHash)(void * );

typedef struct {
  size_t M;
  TFHash fh;
  TLG * v;
}
TH;

/* functii tabela hash */
TH * InitTH(size_t M, TFHash fh);
void DistrTH(TH ** aa, TF fe);
void AfiTHCase1(TH * a, TF afiEl);
void AfiTHCase2(TH * ah, char * character, char * len, TF afi_elem);
void AfiTHCase3(TH * ah, char * nr, TF afi_elem);
int InsTH(TH * a, void * ae, TFCmp f);

// Lab 4:
void * Sublista(void * el, TFCmp fcmp);
int InsTHOrd(TH * a, void * ae, TFCmp fcmp, TFCmp fcmpSort);
void Ins_OrdLG1(TLG * aL, void * elem);
void * CautaTH(TH * a, void * x, TFCmp fcmpSort);

#endif