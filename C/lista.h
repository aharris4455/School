#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

struct DblSolmu
{
  double data; /*Stored number*/
  struct DblSolmu *seur; /*Pointer to next element*/
};

typedef struct DblSolmu DblSolmu;

DblSolmu * ds_luo(double data, DblSolmu *seur);

struct DblLista
{
  size_t n; /*Size of list*/
  DblSolmu *paa; /*Pointer to first element*/
};

typedef struct DblLista DblLista;

DblLista * dl_luo(void);

void dl_tuhoa(DblLista *dl);

DblSolmu * dl_lisaaEteen(DblLista *dl, double arvo);

double dl_poistaEdesta(DblLista *dl);

void dl_tulosta(const DblLista *lista);

double dl_alkio(const DblLista *lista, size_t i);

DblSolmu * dl_lisaa(DblLista *lista, size_t i, double arvo);

double dl_poista(DblLista *lista, size_t i);

