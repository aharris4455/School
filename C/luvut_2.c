#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
    int i,j,k, print_flag, div_flag;
    int start_val = atoi(argv[1]);
    int end_val = atoi(argv[2]);
    int len = argc - 3;
    int *values = (int *)malloc(len*sizeof(int));
    if(values == NULL){
        fprintf(stderr, "Malloc Failed\n");
        return 1;
    }
    /*Populates values with the values to use 
    in the modulo operation*/
    for(i = 0; i < len; ++i){
        values[i] = atoi(argv[i+3]);
    }
    /*
    Compare the values and only print the ones that 
    are not divisible by the values
    */
    print_flag = 1; /*Flag that checks if first print*/
    for(j = start_val; j <= end_val; ++j){
        div_flag = 0; /*Flag to check divisibility*/
        for(k = 0; k < len; ++k){
            if(j%values[k] == 0){
                div_flag = 1;
                break;
            }
        }
        if(!div_flag){
            if(print_flag){
                printf("%d", j);
                print_flag = 0;
            }
            else{
                printf(" %d", j);
            }
        }
    }
    if(!print_flag){
        printf("\n"); 
    }
    free(values);
    return 0;
}