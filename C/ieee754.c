#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[]){
    int len,i, index, CORR_TERM, sum_2, EXP;
    float sum_1;
    char SIGN = argv[1][0];
    CORR_TERM = 127; /*Correction Term*/
    len = 0;
    while(argv[1][len] != '\0'){
        ++len;
    }
    sum_1 = 0.0;
    index = 1;
    for(i = 9; i < len; i++){
        if(argv[1][i] == '1'){
            sum_1 += pow(0.5, index);
        }
        index++;
    }
    printf("%.*f\n",15,1+sum_1);
    sum_2 = 0;
    for(i = 1; i < 9; i++){
        if(argv[1][i] == '1'){
            sum_2 += pow(2, 9-i-1);
        }
    }
    EXP = sum_2 - CORR_TERM;
    printf("%d\n",EXP);
    if(SIGN == '1'){
        printf("%c\n",'-');
        printf("-%.*f\n",15, (1+sum_1)*pow(2,EXP));
    }
    else{
        printf("%c\n", '+');
        printf("%.*f\n",15, (1+sum_1)*pow(2,EXP));
    }
    return 0;
}