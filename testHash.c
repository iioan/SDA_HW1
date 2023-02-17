/* TEODORESCU Ioan - 313CB*/
/*-- testHash.c  */
#include <stdio.h>

#include "tlg.h"

#include "thash.h"

#include <string.h>

#define MAX 5 /* număr maxim de elemente din lista */
#define MAX1 4000

// functia hash curs 
int codHash(void * element) {
  TCuvant * carte = (TCuvant * ) element;
  char * word = carte -> word;
  return *word - 'a';
}

// afiseaza elementele din sublista
void afisarecuvant(void * element) {
  TCuvant * cuvant = (TCuvant * ) element;
  printf("%s/%d", cuvant -> word, cuvant -> count);
}

// functia hash
int codHashcuvant(void * element) {
  TCuvant * cuvant = (TCuvant * ) element;
  char * word = cuvant -> word;
  if ( * word >= 'A' && * word <= 'Z')
    return *word - 'A';
  return *word - 'a';
}

// elibereaza memoria
void freecuvant(void * element) {
  TCuvant * cuvant = (TCuvant * ) element;
  free(cuvant -> word);
  free(cuvant);
}

// compara sizeul sublistei cu lungimea cuvantului
int cmpcuvantLung(void * e1, void * e2) {
  TElem * cuvant1 = (TElem * ) e1;
  TCuvant * cuvant2 = (TCuvant * ) e2;

  return (cuvant1 -> size) - strlen(cuvant2 -> word);
}

// compara 
int cmpcuvant(void * e1, void * e2) {
  TCuvant * cuvant1 = (TCuvant * ) e1;
  TCuvant * cuvant2 = (TCuvant * ) e2;

  if (strcmp(cuvant1 -> word, cuvant2 -> word) != 0)
    return 0;

  if (cuvant1 -> count != cuvant2 -> count)
    return 0;

  return 1;
}

// genereaza tabela hash
TH * GenerareHashcuvant(TLG L) {
  TH * h = NULL;
  TLG p;
  TCuvant * cuvant;
  int rez;

  /* calcul dimensiuni maxime pt tabela hash */
  size_t M = ('Z' - 'A') + 1;

  /* initializare tabela hash */
  h = (TH * ) InitTH(M, codHashcuvant);
  if (h == NULL)
    return NULL;

  for (p = L; p != NULL; p = p -> urm) {
    // parcurge fiecare element din lista
    cuvant = (TCuvant * ) calloc(1, sizeof(TCuvant));
    if (cuvant == NULL)
      return h;

    memcpy(cuvant, p -> info, sizeof(TCuvant));
    // insereaza in th
    rez = InsTHOrd(h, cuvant, cmpcuvant, cmpcuvantLung);

    if (!rez) {
      free(cuvant);
      return h;
    }
  }

  return h;
}

/* return: <0 daca e1<e2, 0 daca e1==e2, >0 daca e1>e2
 */
int comp_carti(void * e1, void * e2) {
  TCuvant * c1 = (TCuvant * ) e1;
  TCuvant * c2 = (TCuvant * ) e2;

  return strcmp(c1 -> word, c2 -> word);
}

// citeste textul, adaugand elementele intr - o lista
void Citire(TLG * L, char * s) {
  TCuvant * elem;
  char * p = strtok(s, " 125");
  while (p) {
    if (strlen(p) > 2) {

      if ( * (p + strlen(p) - 1) == '.' || * (p + strlen(p) - 1) == ',')
        *(p + strlen(p) - 1) = 0;
      elem = (TCuvant * ) calloc(1, sizeof(TCuvant));
      if (!elem)
        return;

      elem -> word = (char * ) calloc(50, sizeof(char));

      memcpy(elem -> word, p, strlen(p) + 1);

      Inserare(L, elem, comp_carti);
    }
    p = strtok(NULL, " 125");
  }
}

int main(int argc, char * input[]) {
  TLG L = NULL;
  TH * h = NULL;
  argc++;
  FILE * f = fopen(input[1], "rt");
  char * s;
  s = (char * ) calloc(MAX1, sizeof(char));
  //cat timp se citesc paragrafe din fisier continua
  while (fscanf(f,"%[^\n]%*c", s) == 1) {
    s[strcspn(s, "\n")] = 0;
    char * token = strtok(s, " ");
    if (strcmp("insert", token) == 0) {
      strcpy(s, s + 7);
      Citire( & L, s);
      h = GenerareHashcuvant(L);
    }
    if (strcmp("print", token) == 0) {
      
      token = strtok(NULL, " ");
      char * token2 = strtok(NULL, " ");
      // cazul print
      if (token == NULL && token2 == NULL)
        AfiTHCase1(h, afisarecuvant);
      // cazul print a 3
      else if (token != NULL && token2 != NULL) {
        AfiTHCase2(h, token, token2, afisarecuvant);
      }
      // cazul print n
      else if (token != NULL && token2 == NULL) {
        AfiTHCase3(h, token, afisarecuvant);
      }
    }
  }
  // eliberez memoria
  DistrugeLG( & L, free);
  DistrTH( & h, free);
  free(s);
  fclose(f);
  return 0;
}