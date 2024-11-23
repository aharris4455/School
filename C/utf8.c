#include "utf8.h"

void utf8_koodaa(unsigned int merkki, unsigned char utf8[]){
    int numBits = sizeof(unsigned int)*CHAR_BIT;
    int i, index, oneIndex, codeLength, numBytes;
    index = 0;
    oneIndex = 0;
    for(i = 0; i < numBits; i++){
        int bit = (merkki >> i) & 1;
        /*printf("%d",bit);*/
        if(bit == 1){
            oneIndex = index;
        }
        index++;
    }  
    /*printf("\n");
    printf("one index<: %d\n",oneIndex);*/
    codeLength = oneIndex + 1; 
    /*Changing codelength to use binary comparison*/
    if(merkki < 0x80){ /*codeLength < 8*/
        numBytes = 1;
        utf8[0] = 0;
        utf8[1] = '\0';
        utf8[0] = merkki & 0x7F;
        /*printf("One byte: %d\n", utf8[0]);*/
    }
    /*codeLength >= 8 && codeLength < 12*/
    else if (merkki < 0x800){
        numBytes = 2;
        utf8[0] = 0xC0; /*0b11000000*/
        utf8[1] = 0x80; /*0b10000000*/
        utf8[2] = '\0';
        utf8[0] |= (merkki >> 6) & 0x1F;
        utf8[1] |= merkki & 0x3F;
        /*printf("Two byte: %d\n", utf8[0]);*/
    }
    /*codeLength >= 12 && codeLength < 16*/
    else if (merkki < 0x10000){
        numBytes = 3;
        utf8[0] = 0xE0; /*0b11100000*/
        utf8[1] = utf8[2] = 0x80; /*0b10000000*/
        utf8[3] = '\0';
        /*take the first 4 bits, then two sets of 6*/
        utf8[0] |= (merkki >> 12) & 0x0F;
        utf8[1] |= (merkki >> 6) & 0x3F;
        utf8[2] |=  merkki & 0x3F;
        /*printf("Three byte: %d %d %d\n", utf8[0], utf8[1], utf8[2]);*/

    }
    else{
        numBytes = 4;
        utf8[0] = 0xF0; /*0b11100000*/
        utf8[1] = utf8[2] = utf8[3] = 0x80; /*0b10000000*/
        utf8[4] = '\0';
        utf8[0] |= (merkki >> 18) & 0x07;
        utf8[1] |= (merkki >> 12) & 0x3F;
        utf8[2] |= (merkki >> 6) & 0x3F;
        utf8[3] |= merkki & 0x3F;
        /*printf("Four byte: %d %d %d %d\n", utf8[0], utf8[1], utf8[2], utf8[3]);*/
    } 
    /*printf("Number of bytes: %d\n", numBytes);
    Take the code point (merkk)
      detrermine the number of bytes needed (numBytes)
      init the array (utf8) to 0
      fill the arry with prefixes according to numBytes*/
    

}