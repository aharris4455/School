#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[]){
    /*Gets an input x then some more inputs
    Takes the sqrt of the other inputs and
    Prints them with x decimal points*/
    int x = atoi(argv[1]);
    int i;
    for(i = 2; i < argc; ++i){
        double current = atof(argv[i]);
        double current_sqrt = sqrt(atof(argv[i]));
        printf("sqrt(%.*f) = %.*f",x,current,x,current_sqrt);
        printf("\n");
    }
    return 0;
}