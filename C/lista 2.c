#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

Solmu * s_luo(const void *data, size_t dataKoko, Solmu *seur)
{
  Solmu *ds = malloc(sizeof(Solmu));
  ds->data = malloc(dataKoko);
  memcpy(ds->data, data, dataKoko);
  ds->seur = seur;
  return ds;
}

Lista * ll_luo(size_t dataKoko, void(*tulostaArvo)(FILE *virta, const void *arvo)){
  Lista *dl = malloc(sizeof(Lista));
  dl->n = 0;
  dl->paa = NULL;
  dl->tulostaArvo = tulostaArvo;
  dl->dataKoko = dataKoko;
  return dl;
}

void ll_tuhoa(Lista *dl)
{
  while(dl->n > 0)
  {
    ll_poistaEdesta(dl);
  }
  free(dl);
}

Solmu * ll_lisaaEteen(Lista *dl, const void *arvo)
{
  dl->paa = s_luo(arvo, dl->dataKoko, dl->paa);
  dl->n += 1;
  return dl->paa;
}

void ll_poistaEdesta(Lista *dl)
{
  if(dl->n > 0)
  {
    Solmu *vanhaPaa = dl->paa;
    dl->paa = dl->paa->seur;
    free(vanhaPaa->data);
    free(vanhaPaa);
    dl->n -= 1;
  }
}

void ll_tulosta(const Lista *lista, FILE *virta)
{
  Solmu *s;
  printf("Lista:");
  for(s = lista->paa; s != NULL; s = s->seur)
  {
    if(lista->tulostaArvo == NULL){
        return;
    }
    printf(" ");
    lista->tulostaArvo(virta, s->data);
  }
  printf("\n");
}