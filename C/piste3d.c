#include "piste3d.h"

double etaisyys(Piste3D a, Piste3D b){
    /*Euclidian distance sqrt( (x1-x2)^2 + (y1-y2)^2 + (z1-z2)^2 )*/
    double x1 = a.x;
    double x2 = b.x;
    double y1 = a.y;
    double y2 = b.y;
    double z1 = a.z;
    double z2 = b.z;

    double part_x = pow((x1-x2),2);
    double part_y = pow((y1-y2),2);
    double part_z = pow((z1-z2),2);

    double sum = part_x + part_y + part_z;

    return sqrt(sum);
}

void tulosta(Piste3D p, int tarkkuus){
    printf("(");
    printf("%.*f, ", tarkkuus, p.x);
    printf("%.*f, ", tarkkuus, p.y);
    printf("%.*f", tarkkuus, p.z);
    printf(")");
}