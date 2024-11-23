/* 
Luvut ohjelma
Aukusti Harris
*/

#include <stdio.h>

int main(void) {
    unsigned int i = 0;
    unsigned int n = 100;
    int lastNum = 0;
    for(i = 0; i <= 100; ++i){
        if(i%2 !=0 && i%3 != 0 && i%5 != 0){
            lastNum = i;
        }
    }
    /*printf("%d\n",lastNum);*/
    for(i=0; i <= n; ++i){
        if(i != lastNum){
            if(i%2 !=0 && i%3 != 0 && i%5 != 0){
                printf("%d ", i);
            }
        }
        else{
            printf("%d", i);
        }
    }
    printf("\n");
    return 0;
}
