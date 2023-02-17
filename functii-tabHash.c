/* TEODORESCU Ioan - 313CB*/
/*  functii-tabHash.c - functii tabela hash */
#include "thash.h"

//initializeaza tabela hash
TH * InitTH(size_t M, TFHash fh) {
  // intra in functie
  TH * h = (TH * ) calloc(sizeof(TH), 1);
  if (!h) {
    printf("eroare alocare hash\n");
    return NULL;
  }

  h -> v = (TLG * ) calloc(M, sizeof(TLG));
  if (!h -> v) {
    printf("eroare alocare vector de pointeri TLG in hash\n");
    free(h);
    return NULL;
  }
  h -> M = M;
  h -> fh = fh;
  return h;
}

//distruge tabela hash
void DistrTH(TH ** ah, TF elib_elem) {
  TLG * p, el, aux;

  /* parcurgere cu pointeri */
  for (p = ( * ah) -> v; p < ( * ah) -> v + ( * ah) -> M; p++) { //vector v
    /* daca exista elemente corespunzatoare acestui hash
     * eliberam info din celula si apoi eliberam celula */
    for (el = * p; el != NULL; el = el -> urm) { // a->v[i]
      for (aux = ((TElem * ) el -> info) -> l; aux != NULL; aux = aux -> urm)
        elib_elem(aux -> info);
    }
  }
  free(( * ah) -> v);
  free( * ah);
  * ah = NULL;
}

//afiseaza toate elementele din th
void AfiTHCase1(TH * ah, TF afi_elem) {
  TLG p;
  int i = 0;
  for (i = 0; i < (int) ah -> M; i++) {
    if (ah -> v[i] != NULL)
      printf("pos %d: ", i);
    for (p = ah -> v[i]; p != NULL; p = p -> urm) {
      printf("(%d:", ((TElem * ) p -> info) -> size);
      TLG q = ((TElem * ) p -> info) -> l;
      for (; q != NULL; q = q -> urm) {
        afi_elem((TCuvant * ) q -> info);
        if ((q -> urm) != NULL)
          printf(", ");
      }
      printf(")");
    }
    if (ah -> v[i] != NULL && i <= 25)
      printf("\n");
  }
}

//afiseaza toate elem care incep cu litera character si au lungimea len
void AfiTHCase2(TH * ah, char * character, char * len, TF afi_elem) {
  int length = atoi(len);
  int cod = ah -> fh( & character);
  if (length < 3) return;
  TLG p;
  if (ah -> v[cod] != NULL)
    for (p = ah -> v[cod]; p != NULL; p = p -> urm) {
      if (((TElem * ) p -> info) -> size == length) {
        printf("(%d:", ((TElem * ) p -> info) -> size);
        TLG q = ((TElem * ) p -> info) -> l;
        for (; q != NULL; q = q -> urm) {
          afi_elem((TCuvant * ) q -> info);
          if ((q -> urm) != NULL)
            printf(", ");
        }
        printf(")");
      }
    }
  if (ah -> v[cod] != NULL) printf("\n");

}

//afiseaza elem din th care au count < un nr 
void AfiTHCase3(TH * ah, char * nr, TF afi_elem) {
  int count = atoi(nr);
  TLG p;
  int i = 0;
  for (i = 0; i < (int) ah -> M; i++) {
    int gasit = 1;
    for (p = ah -> v[i]; p != NULL; p = p -> urm) // lista v
    {
      gasit = 1;
      TLG q = ((TElem * ) p -> info) -> l;
      for (; q != NULL; q = q -> urm) // sublista
      {
        if (((TCuvant * ) q -> info) -> count <= count) {
          gasit = 0;
          break; // break q pentru afisarea pozitiei + newline la sfarsit
        }
      }
      if (gasit == 0) {
        printf("pos%d: ", i);
        break; // break p
      }
    }
    for (p = ah -> v[i]; p != NULL; p = p -> urm) {
      int gasit1 = 1;
      TLG q = ((TElem * ) p -> info) -> l;
      for (; q != NULL; q = q -> urm) // sublista
      {
        if (((TCuvant * ) q -> info) -> count <= count) {
          gasit1 = 0;
          break; // break q pentru gasirea cuvintelor 
        }
      }
      if (gasit1 == 0) {
        printf("(%d: ", ((TElem * ) p -> info) -> size);
        TLG q = ((TElem * ) p -> info) -> l;
        for (; q != NULL; q = q -> urm) {
          int gasit2 = 1;
          if (((TCuvant * ) q -> info) -> count <= count) {
            afi_elem((TCuvant * ) q -> info);
            gasit2 = 0;
          }
          if ((q -> urm) != NULL && gasit2 == 0)
            printf(", ");
        }
        printf(")");
      }
    }
    if (gasit == 0) printf("\n");
  }
}

// creaza subliste/ adauga elemente in sublite
int InsTHOrd(TH * a, void * ae, TFCmp fcmp, TFCmp fcmpSort) {
  int cod = a -> fh(ae);
  // daca exista lista cu size-ul lui ae
  if (CautaTH(a, ae, fcmpSort) == NULL) {
    // creaza sublista si o insereaza in lista generica
    TElem * M = (TElem * ) Sublista(ae, fcmp);
    if (!M) return 0;
    // inserare simpla
    Ins_OrdLG( & a -> v[cod], M);
  } else {
    // cauta sublista cu ac. lungime
    TLG p;
    for (p = a -> v[cod]; p != NULL; p = p -> urm) {
      if (((TElem * ) p -> info) -> size - strlen(((TCuvant * ) ae) -> word) == 0) {
        // inserare ordonata
        Ins_OrdLG1( & (((TElem * ) CautaTH(a, ae, fcmpSort)) -> l), ae);
        break;
      }
    }
  }
  return 1;
}

// initializeaza sublista
void * Sublista(void * el, TFCmp fcmp) {
  TElem * eL = calloc(1, sizeof(TElem)); // lung tgl l
  TCuvant * elem;
  eL -> size = strlen(((TCuvant * ) el) -> word);
  elem = (TCuvant * ) calloc(1, sizeof(TCuvant));
  if (!elem)
    return eL;
  elem -> word = (char * ) calloc(50, sizeof(char));
  memcpy(elem, el, sizeof(TCuvant));
  elem -> count = ((TCuvant * ) el) -> count;
  InsOrd( & eL -> l, elem, fcmp);

  return eL;
}

/*Cauta un element in tabela hash si intoarce pointer catre element sau NULL
 daca acesta nu exista.
*/
void * CautaTH(TH * a, void * x, TFCmp fcmpSort) {
  int cod = a -> fh(x);

  for (TLG L = a -> v[cod]; L; L = L -> urm) {
    if (fcmpSort((TElem * ) L -> info, x) == 0)
      return L -> info;
  }

  return NULL;
}