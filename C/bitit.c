#include "bitit.h"
/*
void scharBitit(signed char x){
    int i, zeroCount, oneCount;
    printf("%d\n",x);
    zeroCount = 0;
    oneCount = 0;
    for(i = CHAR_BIT - 1; i >= 0; i--){
        printf("%d", (x >> i) & 1);
        (x>>i)&1 used to isolaite the ith bit
        if(((x >> i) & 1) == 1){
            oneCount++;
        }
        else{
            zeroCount++;
        }
    }
    printf("\n");
    printf("%d\n", zeroCount);
    printf("%d\n", oneCount);
}

void shortBitit(short int x){
    int i, zeroCount, oneCount;
    printf("%d\n", x);
    zeroCount = 0;
    oneCount = 0;
    for(i = sizeof(short int)*CHAR_BIT - 1; i >= 0; i--){
        printf("%d", (x >> i) & 1);
        if(((x >> i) & 1) == 1){
            oneCount++;
        }
        else{
            zeroCount++;
        }
    }
    printf("\n");
    printf("%d\n", zeroCount);
    printf("%d\n", oneCount);
}

void intBitit(int x){
    int i, zeroCount, oneCount;
    printf("%d\n", x);
    zeroCount = 0;
    oneCount = 0;
    for(i = sizeof(int)*CHAR_BIT - 1; i >= 0; i--){
        printf("%d", (x >> i) & 1);
        if(((x >> i) & 1) == 1){
            oneCount++;
        }
        else{
            zeroCount++;
        }
    }
    printf("\n");
    printf("%d\n", zeroCount);
    printf("%d\n", oneCount);
}

void longBitit(long int x){
    int i, zeroCount, oneCount;
    printf("%d\n", x);
    zeroCount = 0;
    oneCount = 0;
    for(i = sizeof(long int)*CHAR_BIT - 1; i >= 0; i--){
        printf("%d", (x >> i) & 1);
        if(((x >> i) & 1) == 1){
            oneCount++;
        }
        else{
            zeroCount++;
        }
    }
    printf("\n");
    printf("%d\n", zeroCount);
    printf("%d\n", oneCount);
}
*/
void kaannaScharBitit(signed char *x){
    int i;
    unsigned char rev, x_us;
    /*signed char rev_sc;*/
    rev = 0;
    x_us = (unsigned char)*x;
    for(i = 0; i < CHAR_BIT; i++){
        rev <<= 1;
        if(x_us & 1){
            rev |= 1;
        }
        x_us >>= 1;
    }
    *x = (signed char)rev;
    /*printf("%d\n", rev_sc);
    for (i = CHAR_BIT - 1; i >= 0; i--) {
        printf("%d", (rev >> i) & 1);
    }
    printf("\n");*/
    
}

void kaannaShortBitit(short int *x){
    int i;
    unsigned short int rev, x_us;
    /*short int rev_sc;*/
    rev = 0;
    x_us = (unsigned short int)*x;
    for(i = 0; i < sizeof(short int)*CHAR_BIT; i++){
        rev <<= 1;
        if(x_us & 1){
            rev |= 1;
        }
        x_us >>= 1;
    }
    *x = (short int)rev;
    /*printf("%d\n", rev_sc);
    for(i = sizeof(short int)*CHAR_BIT-1; i >= 0; i--){
        printf("%d", (rev >> i) & 1);
    }
    printf("\n");*/
}

void kaannaIntBitit(int *x){
    int i;
    unsigned int rev, x_us;
    /*int rev_sc;*/
    rev = 0;
    x_us = (unsigned int)*x;
    for(i = 0; i < sizeof(int)*CHAR_BIT; i++){
        rev <<= 1;
        if(x_us & 1){
            rev |= 1;
        }
        x_us >>= 1;
    }
    *x = (int)rev;
    /*printf("%d\n",rev_sc);
    for(i = sizeof(int)*CHAR_BIT - 1; i >= 0; i--){
        printf("%d",(rev >> i)&1);
    }
    printf("\n");*/
}

void kaannaLongBitit(long *x){
    int i;
    unsigned long int rev, x_us;
    /*long int rev_sc;*/
    rev = 0;
    x_us = (unsigned long int)*x;
    for(i = 0; i < sizeof(long int)*CHAR_BIT; i++){
        rev <<= 1;
        if(x_us & 1){
            rev |= 1;
        }
        x_us >>= 1;
    }
    *x = (long int)rev;
    /*printf("%ld\n", rev_sc);
    for(i = sizeof(long int)*CHAR_BIT - 1; i >= 0; i--){
        printf("%d", (rev >> i) & 1);
    }*/
}