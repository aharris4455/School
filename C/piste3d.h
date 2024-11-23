#ifndef piste3d_h
#define piste3d_h
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Piste3D {
    double x;
    double y;
    double z;
} Piste3D;

double etaisyys(Piste3D a, Piste3D b);
void tulosta(Piste3D p, int tarkkuus);

#endif
