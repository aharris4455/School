/**
 * @file tilastoja.c
 * @author Aukusti Harris
 */

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]){
    int i,j,k,m,n,l,o,p,q;
    int MAX_COUNT, count,printed,unique;
    double MAX_NUM,MIN_NUM,current,other;
    /*Find the minimum number*/
    for(j = 1; j <= argc - 1; ++j){
        current = atof(argv[j]);
        if(j == 1){
            MIN_NUM = current;
        }
        else if(current >= MIN_NUM){
            continue;
        }
        else{
            MIN_NUM = current;
        }
    }
    printf("Pienin: %4f\n", MIN_NUM);
    /*Find the maximum number*/
    for(i = 1; i <= argc - 1; ++i){
        current = atof(argv[i]);
        if(i == 1){
            current = MAX_NUM;
        }
        else if(current <= MAX_NUM){
            continue;
        }
        else{
            MAX_NUM = current;
        }
    }
    printf("Suurin: %4f\n", MAX_NUM);
    
    /*Find unique numbers*/
    unique = 0;
    for(k = 1; k <= argc - 1; ++k){
        /*Iterate through array and compare current to all other numbers*/
        current = atof(argv[k]);
        count = 0;
        for(m = 1; m <= argc - 1; ++m){
            other = atof(argv[m]);
            if(current == other){
                count++;
            }
        }
        if(count == 1){
            if(!unique){
                printf("Ainutlaatuiset:");
                unique = 1; 
            }
            printf(" %4f", current);
        }
    }
    if(unique){
        printf("\n");
    }
    /*Find the number(s) that appear the most*/
    /*Here we are finding MAX_COUNT*/
    MAX_COUNT = 0;
    for(n = 1; n <= argc - 1; ++n){
        current = atof(argv[n]);
        count = 0; 
        for(l = 1; l <= argc - 1; ++l){
            other = atof(argv[l]);
            if(current == other){
                count++;
            }
        }
        if(count > MAX_COUNT){
            MAX_COUNT = count;
        }
    }
    /*Here we print all numbers that apper MAX_COUNT times*/
    if(MAX_COUNT > 1){
        printf("Useimmiten esiintyneet (%d kertaa):", MAX_COUNT);
        for(o = 1; o <= argc - 1; ++o){
            current = atof(argv[o]);
            count = 0;
            for(p = 1; p <= argc - 1; ++p){
                other = atof(argv[p]);
                if(current == other){
                    count++;
                }
            }
            if(count == MAX_COUNT){
                printed = 0; /*Check if current num has been printed already*/
                for(q = 1; q < o; ++q){
                    if(atof(argv[q]) == current){
                        printed = 1;
                        break;
                    }
                }   
                if(!printed){
                    printf(" %4f", current);
                }
            }
        }
        printf("\n");
    }
    return 0;
}

