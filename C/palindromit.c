#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
/**
 * @brief FInd palindromes
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc, char *argv[]){
    int i,j,len,IS_NOT_PAL;
    for(i = 1; i < argc; ++i){
        char *current = argv[i];
        len = 0;
        /*Get the length of the word*/
        while(current[len] != '\0'){
            len++;
        }
        /*Compare the chars of the word*/
        for(j = 0; j < len/2; ++j){
            char current_char = tolower(current[j]);
            char other = tolower(current[len-j-1]);
            IS_NOT_PAL = 1;
            if(current_char != other){
                IS_NOT_PAL = 0;
                break;
            }
        }
        if(IS_NOT_PAL == 0){
            printf("\"%s\": ei ole palindromi", current);
            printf("\n");
        }
        else{
            printf("\"%s\": on palindromi", current);
            printf("\n");
        }
    }
    return 0; 
}