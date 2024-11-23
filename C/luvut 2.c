#include <stdio.h>
#include <stdlib.h>

static int dblLaskevaVrt(const void *a, const void *b)
{
  const double *x = a; /* Funktio olettaa, että a ja b osoittavat */
  const double *y = b; /* double -arvoihin. */
  return (*x < *y) ? -1 : ((*x > *y) ? 1 : 0); /* Osoitettujen arvojen vertailu. */
} 



int main(int argc, char *argv[]){
    size_t koko = 2;
    double *array;
    double input;
    int count = 0;
    double sum, avg;
    int i;
    /*Gotta manually allocate space for the stored numbers*/
    array = (double *)malloc(koko * sizeof(double));
    while(scanf("%lf", &input) == 1){
        if(count == koko){
            koko *= 2;
            array = realloc(array, koko*sizeof(double));
        }
        array[count] = input;
        count++;
    }
    array = realloc(array, count*sizeof(double));
    qsort(array, count, sizeof(double), dblLaskevaVrt);
    sum = 0;
    printf("Luettiin %d lukua:", count);
    for(i = 0; i < count; i++){
        printf(" %.3f", array[i]);
        sum += array[i];
    }
    printf("\n");
    avg = sum/count;
    printf("Summa: %.3f\n",sum);
    printf("Keskiarvo: %.3f\n", avg);
    free(array);
    return 0;
}
