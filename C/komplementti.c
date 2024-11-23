#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[]){
    int i, len, sum;
    char SIGN = argv[1][0];
    len = 0;
    /* Calc length of bit string*/
    while (argv[1][len] != '\0'){
        len++;
    }
    sum = 0;
    for(i = 1; i < len; i++){
        if(argv[1][i] == '1'){
            sum += pow(2, len-i-1);
        }
    }
    if(SIGN == '1'){
        sum = -(sum-(1 << (len-1)));
        printf("-%d\n", sum);
    }
    else{
        printf("%d\n", sum);
    }
    
    return 0;   
}