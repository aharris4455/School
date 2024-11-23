#include "mjonot.h"

char **kopioi_mjt(char **mjt, size_t lkm){
    int i,j;
    char **t = malloc(lkm * sizeof(char *));
    if(t == NULL){
        printf("Memory Allocation Failed\n");
        return NULL;
    }
    for(i = 0; i < lkm; i++){
        /*Allocation of memory for each indivual word*/
        t[i] = malloc((strlen(mjt[i]) + 1) * sizeof(char)); 
        if(t[i] == NULL){
            printf("Allocation failed for word\n");
            for(j = 0; j < i; j++){
                free(t[j]);
            }
            free(t);
            return NULL;
        }
        strcpy(t[i], mjt[i]);
    }
    return t;
}