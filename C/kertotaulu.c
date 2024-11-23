/*
Aukusti Harris
Kertotaulu ohjelma
*/

#include <stdio.h>

int main(void){
    int x_axis[16];
    int y_axis[16];
    int i, j, k, m, count;
    /*Populate axis vectors */
    for(i=0; i <= 15; ++i){
        x_axis[i] = i;
        y_axis[i] = i;
    }


    for(j = 0; j <= 15; ++j){

        if(j < 1){                    /* If j < 1, print x*/
            printf("%4s", "x");

            for(m = 1; m <= 15; ++m){   /* Print rest of multiplication y axis */
                printf("%4d", y_axis[m]);
            }
            
        }
        else{
            count = 0;
            for(k = 0; k <= 15; ++k){
                if(k < 1){
                    if(count < 1){
                        printf("%4d", j);
                        count++;
                    }
                }
                else{
                    printf("%4d", x_axis[k]*j);
                }
            }
        }
        printf("\n");
    }
    return 0;
}
