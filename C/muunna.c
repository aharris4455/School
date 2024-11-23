#include "muunna.h"

void muunnaTaulu(unsigned int koko, double *taulu, double (*muunnos)(double)){
    /*Takes the values from the input array and passes them through the passed function*/
    int i;
    for(i = 0; i < koko; i++){
        taulu[i] = muunnos(taulu[i]);
    }
}