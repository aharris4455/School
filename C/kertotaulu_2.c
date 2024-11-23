/**
 * @file kertotaulu_2.c
 * @author Aukusti  Harris
 * @date 2024-05-27
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    int a = atoi(argv[1]); 
    int b = atoi(argv[2]);
    int c = atoi(argv[3]);
    int d = atoi(argv[4]); 
    int i,j,k,line_count,count;
    int MAX_NUM = b*d;
    int current = MAX_NUM;
    count = 0;
    while(1){
        count++;
        if(current < 1){
            break;
        }
        else{
            current = current/10;
        }
    }
    
    line_count = 0;
    if (line_count < 1){
        line_count++;
        printf("%*c", count,' '); 
        for(k = a; k <= b; ++k){
            printf("%*d",count, k);
        }
        printf("\n");
    }
    for(i = c; i <= d; ++i){
        printf("%*d",count, i);
        for(j = a; j <= b; ++j){
            printf("%*d",count, i*j); 
        }
        printf("\n");
    }
    return 0;
}