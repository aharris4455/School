#ifndef kuukaudet_h
#define kuukaudet_h
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>

enum kuukaudet{
    TAMMIKUU = 0,
    HELMIKUU,
    MAALISKUU,
    HUHTIKUU,
    TOUKOKUU,
    KESAKUU,
    HEINAKUU,
    ELOKUU,
    SYYSKUU,
    LOKAKUU,
    MARRASKUU,
    JOULUKUU,
    KK_LKM = 12
};

extern const char *KK_NIMET[KK_LKM];
extern const char KK_PAIVAT[2][KK_LKM];

int karkausvuosi(int vuosiluku);
char kkPituus(const char *kkNimi, int vuosiluku);

#endif