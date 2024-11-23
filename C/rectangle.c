#include "rectangle.h"

Rectangle * createRectangle(){
    /*(Rectangle *) => typecasting, changes the malloc void pointer
    to a Rectangle pointer*/
    Rectangle *rect = (Rectangle *)malloc(sizeof(Rectangle)); 
    rect->height = 0;
    rect->width = 0;
    rect->origin.x = 0;
    rect->origin.y = 0;
    return rect;
}

Rectangle * createRectangle2(Point p){
    Rectangle *rect = (Rectangle *)malloc(sizeof(Rectangle));
    rect->height = 0;
    rect->width = 0;
    rect->origin.x = p.x;
    rect->origin.y = p.y;
    return rect;
}

Rectangle * createRectangle3(int w, int h){
    Rectangle *rect = (Rectangle *)malloc(sizeof(Rectangle));
    rect->height = h;
    rect->width = w;
    rect->origin.x = 0;
    rect->origin.y = 0;
    return rect;
}

Rectangle * createRectangle4(Point p, int w, int h){
    Rectangle *rect = (Rectangle *)malloc(sizeof(Rectangle));
    rect->height = h;
    rect->width = w;
    rect->origin.x = p.x;
    rect->origin.y = p.y;
    return rect;
} 

void move(Rectangle *r, int x, int y){
    r->origin.x = x;
    r->origin.y = y;
}

int getArea(const Rectangle *r){
    int area;
    area = r->height*r->width;
    return area;
}
