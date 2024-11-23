#include "kertotaulu.h"

Kertotaulu *luoKertotaulu(uint a, uint b, uint c, uint d){
    Kertotaulu *kt = (Kertotaulu *)malloc(sizeof(Kertotaulu));
    /*Set the values of a-d*/
    uint rows, cols, i, j;
    kt->a = a;
    kt->b = b;
    kt->c = c;
    kt->d = d;
    /*Calculate the rows and columns*/
    rows = d-c+2;
    cols = b-a+2;
    /*Allocate space for the rows*/
    kt->kertotaulu = (uint **)malloc(rows*sizeof(uint*));
    for(i = 0; i < rows; i++){
        /*Allocate space for the columns*/
        kt->kertotaulu[i] = (uint *)malloc(cols*sizeof(uint));
        for(j = 0; j < cols; j++){
            /*Fill the table*/
            if(j == 0){
                kt->kertotaulu[i][j] = (c+i)-1;
            }
            else if(i == 0){
                kt->kertotaulu[i][j] = (a+j)-1;
            }
            else{
                kt->kertotaulu[i][j] = (a+j-1)*(c+i-1);
            }
        }
    }
    return kt;
}

void tuhoaKertotaulu(Kertotaulu *kt){
    /*Calculate the rows*/
    uint rows, i;
    rows = (kt->d - kt->c) + 2;
    for(i = 0; i < rows; i++){
        /*Free each row*/
        free(kt->kertotaulu[i]);
    }
    /*Free the table*/
    free(kt->kertotaulu);
    free(kt);
}