#include "vaihto.h"

void vaihda(int *a, int *b){
    int temp;
    temp = *a; /*Deref. to ge the values of the var they point to (A mem. addr. is passed*/
    *a = *b; /*Swap a and b*/
    *b = temp;
}

void jarjesta(int *a, int *b, int *c){
    /*Output should be in ascending order so a,b,c i.e. a is smallest c is largest*/
    if(*a > *b){
        vaihda(a,b);
    }
    if(*a > *c){
        vaihda(a, c);
    }
    if(*b > *c){
        vaihda(b, c);
    }

}