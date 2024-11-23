#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]){
    int i;
    for(i = 1; i < argc; ++i){
        unsigned int length = (unsigned int) strlen(argv[i]);
        printf("%d: %s (pituus: %u)\n",i,argv[i],length);
    }
    return 0;
}