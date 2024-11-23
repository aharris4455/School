#include "fibonacci.h"

unsigned int *fib_jono(unsigned int n){
    /*Fi = Fi-1 + Fi-2*/
    int i;
    unsigned int *x;
    x = (unsigned int *)malloc(n * sizeof(unsigned int));
    if(x == NULL){
        printf("Memory allocation failed\n");
        return NULL;
    }
    else{
        if(n > 0) x[0] = 0;
        if(n > 1) x[1] = 1;
        for(i = 2; i < n; i++){
            x[i] = x[i-1]+x[i-2]; 
        }
        return x;
    }
}