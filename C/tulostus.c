#include "tulostus.h"

void tulostaDblTaulu(double *taulu, size_t lkm, const char *taulNimi, int tarkkuus, const char *tiedNimi){
    FILE *fptr;
    int i;
    double current;
    fptr = fopen(tiedNimi, "w");
    if(fptr == NULL){
        printf("Error: Cannot open file \n");
        exit(0);
    }
    else{
        for(i = 0; i < lkm; i++){
            current = taulu[i];
            fprintf(fptr, "%s[%d] = %.*f\n", taulNimi, i, tarkkuus, current);
        } 
    }
}