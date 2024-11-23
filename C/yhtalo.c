/**
 * @file yhtalo.c
 * @author Aukusti Harris
 */
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]){
    double X1, X2, inner;
    double A = atof(argv[1]);
    double B = atof(argv[2]);
    double C = atof(argv[3]);
    inner = (pow(B,2)) - 4*A*C;
    X1 = (-B + sqrt(pow(B,2) - 4*A*C))/(2*A);
    X2 = (-B - sqrt(pow(B,2) - 4*A*C))/(2*A);
    if(inner < 0){
        printf("Ei ratkaisua");
        printf("\n");
    }
    else if(inner == 0){
        printf("%.3f", X1);
        printf("\n");
    }
    else{
        if(X1 < X2){
            printf("%.3f ",X1);
            printf("%.3f", X2);
            printf("\n");
        }
        else{
            printf("%.3f ", X2);
            printf("%.3f", X1);
            printf("\n");
        }
    } 
    return 0;
}   