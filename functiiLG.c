/* TEODORESCU Ioan - 313CB*/
/*--- functiiLG.c -- operatii de baza pentru lista simplu inlantuita generica---*/
#include "tlg.h"

#include "thash.h"

TLG Aloc_CelulaG(void * x) {
  TLG aux;
  aux = (TLG) calloc(1, sizeof(TCelulaG));
  if (!aux)
    return NULL;

  aux -> info = x;
  aux -> urm = NULL;
  return aux;
}

int Ins_IncLG(TLG * aL, void * ae) {
  TLG aux = calloc(1, sizeof(TCelulaG));
  if (!aux)
    return 0;

  aux -> info = ae;
  aux -> urm = * aL;
  * aL = aux;

  return 1;
}

void DistrugeLG(TLG * aL, TF free_elem) /* distruge lista */ {
  while ( * aL != NULL) {
    TLG aux = * aL; /* adresa celulei eliminate */
    if (!aux)
      return;

    free_elem(aux -> info); /* elib.spatiul ocupat de element*/
    * aL = aux -> urm; /* deconecteaza celula din lista */
    free(aux); /* elibereaza spatiul ocupat de celula */
  }
}

void AfisareLG(TLG L, void( * afiEL)(void * )) {
  if (!L) {
    printf("Lista vida\n");
    return;
  }

  printf("Lista: [");
  for (; L; L = L -> urm)
    afiEL(L -> info);

  printf("]\n");
}

void Inserare(TLG * aL, void * elem, int( * comp)(void * , void * )) {
  TLG L = * aL;
  for (; L; L = L -> urm) {
    if (comp(elem, L -> info) == 0) {
      ((TCuvant * )(L -> info)) -> count++;
      return;
    }
  }
  ((TCuvant * )(elem)) -> count++;
  InsOrd(aL, elem, comp);
}

// insereaza elem in lista
void InsOrd(TLG * aL, void * elem, int( * comp)(void * , void * )) {
  TLG L = * aL, ant = NULL;
  TLG celula = Aloc_CelulaG(elem);
  if (!celula)
    return;

  for (; L; ant = L, L = L -> urm) {
    if (comp(elem, L -> info) < 0) {
      // am gasit prima celula pentru care elem < L->info deci
      // elem trebuie plasat direct inaintea celulei curente
      celula -> urm = L;
      if (ant == NULL) {
        * aL = celula;
      } else {
        ant -> urm = celula;
      }
      return;
    }
  }

  if (ant == NULL) {
    * aL = celula;
  } else {
    ant -> urm = celula;
  }
}

// insereaza sublistele in ordine crescatoare
void Ins_OrdLG(TLG * aL, void * elem) {
  TLG L = * aL, ant = NULL;
  TLG celula = calloc(1, sizeof(TCelulaG));
  if (!celula)
    return;
  celula -> info = elem;
  celula -> urm = NULL;

  for (; L; ant = L, L = L -> urm) {
    if (comp_sizes(elem, L -> info) < 0) {
      // am gasit prima celula pentru care elem < L->info deci
      // elem trebuie plasat direct inaintea celulei curente
      celula -> urm = L;
      if (ant == NULL) {
        * aL = celula;
      } else {
        ant -> urm = celula;
      }
      return;
    }
  }

  // Am parcurs toata lista si nu am inserat inca elementul. Inseamna
  // ca e mai mare decat toate elementele deci va fi inserat la final.
  if (ant == NULL) {
    * aL = celula;
  } else {
    ant -> urm = celula;
  }
}

// insereaza elementele din sublista in ordinea precizata
void Ins_OrdLG1(TLG * aL, void * elem) {
  TLG L = * aL, ant = NULL;
  TLG celula = calloc(1, sizeof(TCelulaG));
  if (!celula)
    return;
  celula -> info = elem;
  celula -> urm = NULL;

  for (; L; ant = L, L = L -> urm) {
    if (comp_counts(elem, L -> info) > 0) {
      // am gasit prima celula pentru care elem < L->info deci
      // elem trebuie plasat direct inaintea celulei curente
      celula -> urm = L;
      if (ant == NULL) {
        * aL = celula;
      } else {
        ant -> urm = celula;
      }
      return;
    }
  }

  // Am parcurs toata lista si nu am inserat inca elementul. Inseamna
  // ca e mai mare decat toate elementele deci va fi inserat la final.
  if (ant == NULL) {
    * aL = celula;
  } else {
    ant -> urm = celula;
  }
}

// compara numarul de aparitii
int comp_counts(void * e1, void * e2) {
  TCuvant * cuv1 = (TCuvant * ) e1;
  TCuvant * cuv2 = (TCuvant * ) e2;
  if (cuv1 -> count - cuv2 -> count == 0)
    return strcmp(cuv2 -> word, cuv1 -> word);
  return cuv1 -> count - cuv2 -> count;
}

// compara lungimile
int comp_sizes(void * elem1, void * elem2) {
  int size1 = (int)((TElem * ) elem1) -> size;
  int size2 = (int)((TElem * ) elem2) -> size;
  return size1 - size2;

}