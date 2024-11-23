#include "lista.h"

DblSolmu * ds_luo(double data, DblSolmu *seur)
{
  DblSolmu *ds = malloc(sizeof(DblSolmu));
  ds->data = data;
  ds->seur = seur;
  return ds;
}

DblLista * dl_luo(void)
{
  DblLista *dl = malloc(sizeof(DblLista));
  dl->n = 0;
  dl->paa = NULL;
  return dl;
}

void dl_tuhoa(DblLista *dl)
{
  while(dl->n > 0)
  {
    dl_poistaEdesta(dl);
  }
  free(dl);
}

DblSolmu *dl_lisaaEteen(DblLista *dl, double arvo)
{
  dl->paa = ds_luo(arvo, dl->paa);
  dl->n += 1;
  return dl->paa;
}

DblSolmu *dl_lisaa(DblLista *lista, size_t i, double arvo){
    DblSolmu * new = NULL;
    DblSolmu * u = NULL;
    DblSolmu * curr = NULL;
    DblSolmu * uusi = NULL; 
    size_t j; 
    if(lista->n == 0){
        lista->paa = ds_luo(arvo, NULL);
        lista->n += 1;
        return lista->paa;
    }
    else if(i == 0){
        
        new = dl_lisaaEteen(lista, arvo);
        return new; 
    }
    else if(i >= lista->n){
        u = lista->paa;
        while(u->seur != NULL){
            u = u->seur;
        }
        u->seur = ds_luo(arvo, NULL);
        lista->n += 1;
        return u->seur;
    }
    else{
        curr = lista->paa;
        
        for(j = 0; j < i-1; j++){
            curr = curr->seur;
        }
        uusi = ds_luo(arvo, curr->seur);
        curr->seur = uusi;
        lista->n += 1;
        return uusi; 
    }
}

double dl_poistaEdesta(DblLista *dl)
{
  double arvo = 0;
  if(dl->n > 0)
  {
    DblSolmu *vanhaPaa = dl->paa;
    arvo = dl->paa->data;
    dl->paa = dl->paa->seur;
    free(vanhaPaa);
    dl->n -= 1;
  }
  return arvo;
}

double dl_poista(DblLista *lista, size_t i){
  DblSolmu * curr_1 = NULL;
  DblSolmu * curr_2 = NULL;
  DblSolmu * prev = NULL;
  DblSolmu * next_1 = NULL;
  DblSolmu * next_2 = NULL; 
  double val_1, val_2;
  size_t j; 
  if(i >= lista->n){
    return 0; 
  }
  else if(i == 0){
    curr_1 = lista->paa;
    val_1 = curr_1->data;
    next_1 = curr_1->seur;
    lista->paa = next_1;
    free(curr_1);
    lista->n -= 1;
    return val_1;
  }
  else{
    curr_2 = lista->paa;
    for(j = 0; j < i; j++){
      prev = curr_2;
      curr_2=curr_2->seur;
    }
    val_2 = curr_2->data;
    next_2 = curr_2->seur; 
    prev->seur = next_2;
    free(curr_2);
    lista->n -= 1; 
    return val_2; 
  }
}

void dl_tulosta(const DblLista *lista)
{
  DblSolmu *s;
  printf("Lista:");
  for(s = lista->paa; s != NULL; s = s->seur)
  {
    printf(" %.1f", s->data);
  }
  printf("\n");
}

double dl_alkio(const DblLista *lista, size_t i){
    DblSolmu *s = lista->paa;
    size_t idx = 0;  
    while(s != NULL){
      if(idx == i){
        return s->data;
      }
      s = s->seur;
      idx++;
    }
}
