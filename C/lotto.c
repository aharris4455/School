#include <stdio.h>
#include <stdlib.h>
/*
Input 14 numbers, the first 7 are the correct row 
while the next 7 are the guess row 
Compare these two then output the same numbers, if any
*/
int main(int argc, char *argv[]){
    int correct_row[7];
    int guess_row[7];
    int correct_guess[7];
    int i,j,k,l,m,n,count;
    for(i = 0; i < 7; ++i){
        int x = atoi(argv[i+1]);
        int y = atoi(argv[i+8]);
        correct_row[i] = x;
        guess_row[i] = y;
    }
    printf("Voittorivi: ");
    for(k = 0; k < 7; ++k){
        if(k == 6){
            printf("%d", correct_row[k]);
        }
        else{
            printf("%d ", correct_row[k]);
        }
    }
    printf("\n");
    printf("Lottorivi: ");
    for(j = 0; j < 7; ++j){
        if(j == 6){
            printf("%d", guess_row[j]);
        }
        else{
            printf("%d ",guess_row[j]);
        }
    }
    printf("\n");
    /*
    Compare the correct row to the guess row
    */
   count = 0;

    for(l = 0; l < 7; ++l){
        for(m = 0; m < 7; ++m){
            if(guess_row[l] == correct_row[m]){
                correct_guess[count] = guess_row[l];
                count++;
                break;
            }
        }
    }
    if(count == 0){
        printf("Ei yhtään oikein!\n");
    }
    else{
        printf("%d oikein: ", count);
        for(n = 0; n < count; ++n){
            if(n == count - 1){
                printf("%d", correct_guess[n]);
            }
            else{
              printf("%d ", correct_guess[n]);  
            }
        }
        printf("\n");
    }
    
    return 0; 
}