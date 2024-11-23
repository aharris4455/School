#include "kuukaudet.h"

const char *KK_NIMET[KK_LKM] = {
    "tammikuu", "helmikuu", "maaliskuu", "huhtikuu",
    "toukokuu", "kesäkuu", "heinäkuu", "elokuu",
    "syyskuu", "lokakuu", "marraskuu", "joulukuu"
    };
const char KK_PAIVAT[2][KK_LKM] = {
    {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int karkausvuosi(int vuosiluku){
    /*Leap year if divsible by 4, if end of century number
    it hase to be divsible by 400*/
    if(vuosiluku % 100 == 0){
        if(vuosiluku % 400 == 0){
            return 1;
        }
        else{
            return 0;
        }
    }
    else{
        if(vuosiluku % 4 == 0){
            return 1;
        }
        else{
            return 0;
        }
    }
}

char kkPituus(const char *kkNimi, int vuosiluku){
    int i, leap, nimiIndex;
    char val, lowerNimi[20];
    leap = karkausvuosi(vuosiluku);
    for(i = 0; kkNimi[i] != '\0'; i++){
        lowerNimi[i] = tolower((unsigned char) kkNimi[i]);
    }
    lowerNimi[i] = '\0';
    nimiIndex = -1; /*Init to -1 to indicate not found*/
    for(i = 0; i < KK_LKM; i++){
        if(strcmp(lowerNimi, KK_NIMET[i]) == 0){
            nimiIndex = i;
            break;
        }
    }
    if(nimiIndex == -1){
        return -1;
    }
    val = KK_PAIVAT[leap][nimiIndex];
    return val; 
}
