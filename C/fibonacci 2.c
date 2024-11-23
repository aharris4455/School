#include <stdio.h>
#include "fibonacci.h"

int numDigits(unsigned int num){
    int digits = 0;
    while(num > 0){
        digits++;
        num /= 10;
    }
    return digits;
}

char *fib_jono_mj(unsigned int n){
    unsigned int f0 = 0, f1 = 1, next;
    unsigned int cap = 1; /*Capacity (buffer size)*/
    unsigned int len = 0; /*String length*/
    unsigned int i;
    int m;
    char *fibString = malloc(1); /*1 byte init for null term.*/
    if(n == 0){
        char *emptyString = malloc(1); /*Allocate 1 byte for the null terminator*/
        if(emptyString == NULL){
            printf("Malloc failed: emptyString\n");
            return NULL;
        }
        emptyString[0] = '\0';
        return emptyString;
    }
    
    if(fibString == NULL){
        printf("Malloc failed: fibString\n");
        return NULL;
    }
    fibString[0] = '\0'; /*Start with null term.*/
    for(i = 0; i < n; i++){
        if(i == 0){
            next = f0; /*Sets 0 to be the first value*/
        }
        else if(i == 1){
            next = f1; /*Sets 1 as the first value*/
        }
        else{
            next = f0 + f1; /*Calculate sum of the previous numbers*/
            f0 = f1; /*Shift f0 and f1*/
            f1 = next;
        }
        /*Calculate the number of needed chars to add to the string*/
        /*m = snprintf(NULL, 0, (i == 0) ? "%u" : ", %u", next);*/
        m = numDigits(next);
        /*Make sure theres enough capacity for the next additions*/
        if(i == 0){
            while (len + m + 1 > cap){
                /*printf("cap before double while i = 0: %u\n", cap);*/
                cap *= 2; /*Double Capacity*/
                /*printf("cap after double while i = 0: %u\n", cap);*/
                fibString = realloc(fibString, cap);
                if(fibString == NULL){
                    printf("Realloc failed: fibString\n");
                    return NULL;
                }
            }
            len += sprintf(fibString + len, "%u",next); 
        }
        else{
            while(len + m + 2 + 1 > cap){
                /*printf("cap before double while i > 0: %u\n", cap);*/
                cap *= 2;
                /*printf("cap after double while i > 0: %u\n", cap);*/
                fibString = realloc(fibString, cap);
                if(fibString == NULL){
                    printf("Realloc failed: fibString\n");
                    return NULL;
                }
            }
            len += sprintf(fibString + len, ", %u", next);
        }
    }
    fibString = realloc(fibString, len + 1); /*Reallocate to exact needed size*/
    return fibString;
}