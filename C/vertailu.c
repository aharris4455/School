#include "vertailu.h"
#include "rectangle.h"

int rectAlaVrt(const void *a, const void *b){
    /*Increasing compare*/
    int height_a, height_b, width_a, width_b, area_a, area_b;
    Rectangle* const *rt_a = a; 
    Rectangle* const *rt_b = b;
    height_a = (*rt_a)->height;
    width_a = (*rt_a)->width;
    height_b = (*rt_b)->height;
    width_b = (*rt_b)->width;
    area_a = width_a * height_a;
    area_b = width_b * height_b;
    return (area_a < area_b) ? -1 : ((area_a > area_b) ? 1: 0);
}

int rectXyVrt(const void *a, const void *b){
    /*Increasing order*/
    int x_a, x_b, y_a, y_b;
    Rectangle* const *rt_a = a;
    Rectangle* const *rt_b = b;
    x_a = (*rt_a)->origin.x;
    y_a = (*rt_a)->origin.y;
    x_b = (*rt_b)->origin.x;
    y_b = (*rt_b)->origin.y;
    if(x_a != x_b){
        return (x_a < x_b) ? -1 : 1;
    }
    else{
        if(y_a == y_b){
            return 0;
        }
        else{
            return (y_a < y_b) ? -1 : 1;
        }
    }
}

int rectLeveysVrt(const void *a, const void *b){
    int width_a, width_b;
    Rectangle* const *rt_a = a;
    Rectangle* const *rt_b = b;
    width_a = (*rt_a)->width;
    width_b = (*rt_b)->width;
    return (width_a > width_b) ? -1 : ((width_a < width_b) ? 1 : 0);

}

int mjPitAakkosVrt(const void *a, const void *b){
    size_t len_a, len_b;
    char * const *str_a = a;
    char * const *str_b = b;
    len_a = strlen(*str_a);
    len_b = strlen(*str_b);
    
    if(len_a == len_b){
        return strcmp(*str_a, *str_b);
    }
    else{
        return (len_a > len_b) ? -1 : ((len_a < len_b) ? 1 : 0);
    }
}