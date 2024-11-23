#include "genhaku.h"

size_t etsi(void *mista, size_t n, void *mita, size_t m, size_t koko){
    /*
    Mista = haystack to search from
    n = length of haystack
    mita = needle to search for
    m = length of needle
    koko = size of passed type*/
    size_t i;
    unsigned char *haystack = NULL;
    unsigned char *needle = NULL;
    if(m * koko > n * koko){
        return -1;
    }
    haystack = (unsigned char *)mista;
    needle = (unsigned char *)mita; 
    for(i = 0; i <= (n - m)*koko; i += koko){
        if(memcmp(haystack + i, needle, m*koko) == 0){
            return i/koko;
        }
    }
    return n;
}