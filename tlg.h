/* TEODORESCU Ioan - 313CB*/
/*-- tlg.h --- LISTA SIMPLU INLANTUITA GENERICA ---*/ 
#include <stdlib.h>

#include <stdio.h>

#include <string.h>

#include <stdarg.h>

#include <time.h>

#ifndef _LISTA_GENERICA_
#define _LISTA_GENERICA_

typedef struct celulag {
  void * info; /* adresa informatie */
  struct celulag * urm; /* adresa urmatoarei celule */
}
TCelulaG, * TLG; /* tipurile Celula, Lista  */

typedef struct {
  int size;
  TLG l;
}
TElem;

typedef struct {
  char * word;
  int count;
}
TCuvant;

typedef int( * TFElem)(void * ); /* functie prelucrare element */
typedef int( * TFCmp)(void * , void * ); /* functie de comparare doua elemente */
typedef void( * TF)(void * ); /* functie afisare/eliberare un element */

/* functii lista generica */
int Ins_IncLG(TLG * , void * ); /*- inserare la inceput reusita sau nu (1/0) -*/
void DistrugeLG(TLG * aL, TF fe); /* distruge lista */
int Cautare(TLG * aL, void * elem, int( * comp)(void * , void * ), int( * incr)(void * ));
void InsOrd(TLG * aL, void * elem, int( * comp)(void * , void * ));
void AfisareLG(TLG L, void( * afiEL)(void * ));
void Inserare(TLG * aL, void * elem, int( * comp)(void * , void * ));
int comp_sizes(void * elem1, void * elem2);
int comp_counts(void * e1, void * e2);
void elib_list(TLG * aL, TF free_elem);
void Afisare(TLG * , TF);
void Ins_OrdLG(TLG * aL, void * elem);

#endif