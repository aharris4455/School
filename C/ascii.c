#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
    int start_val = atoi(argv[1]);
    int end_val = atoi(argv[2]);
    /*printf("start: %d, end: %d \n", start_val, end_val);*/
    while(start_val <= end_val){
        printf("%d: %c\n",start_val, start_val);
        start_val++;
    }
    return 0;
}