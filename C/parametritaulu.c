#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char *argv[]){
    int maxIndexLen = 0;
    int maxArgLen = 0;
    int temp,i,j,totWidth,len,spacesNeeded;
    if(argc < 2){
        return 0;
    }
    /*Calcuöate the minimum width of index column*/
    temp = argc - 1;
    while(temp > 0){
        maxIndexLen++;
        temp /= 10;
    }
    /*Clacuölate the max width of the arc column*/
    for(i = 1; i < argc; i++){
        len = strlen(argv[i]);
        if(len > maxArgLen){
            maxArgLen = len;
        }
    }
    /*Printing top border*/
    totWidth = maxIndexLen + 1 + maxArgLen + 3;
    printf("#");
    for(i = 0; i < totWidth + 1; i++){
        printf("#");
    }
    printf("#\n");
    
    /*Printing args*/
    for(i = 1; i < argc; i++){
        printf("# %*d | %-s", maxIndexLen, i, argv[i]);
        spacesNeeded = maxArgLen - strlen(argv[i]) + 1;
        while(spacesNeeded-- > 0){
            printf(" ");
        }
        printf("#\n");
        /*Printing seprators*/
        if(i < argc - 1){
            printf("#");
            for(j = 0; j < maxIndexLen + 2; j++){
                printf("-");
            }
            printf("+");
            for(j = 0; j < maxArgLen + 2; j++){
                printf("-");
            }
            printf("#\n");
        }
    }
    printf("#");
    for(i = 0; i < totWidth + 1; i++){
        printf("#");
    }
    printf("#\n");
    return 0;
}
