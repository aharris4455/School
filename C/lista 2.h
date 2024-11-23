#ifndef lista_h
#define lista_h
#include <stddef.h>
#include <stdio.h>
#include <string.h>

struct Solmu
{
  void *data;
  struct Solmu *seur;
};

typedef struct Solmu Solmu;

Solmu * s_luo(const void *data, size_t dataKoko, Solmu *seur);

struct Lista
{
  size_t n;
  Solmu *paa;
  void (*tulostaArvo)(FILE *virta, const void *arvo);
  size_t dataKoko;
};

typedef struct Lista Lista;

Lista * ll_luo(size_t dataKoko, void(*tulostaArvo)(FILE *virta, const void *arvo));

void ll_tuhoa(Lista *dl);

Solmu * ll_lisaaEteen(Lista *dl, const void *arvo);

void ll_poistaEdesta(Lista *dl);

void ll_tulosta(const Lista *lista, FILE *virta);
#endif
