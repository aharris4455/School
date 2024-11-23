#ifndef rectangle_h
#define rectangle_h
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

struct Point
{
  int x;
  int y;
};

typedef struct Point Point;

struct Rectangle
{
  int width;
  int height;
  Point origin;
};

typedef struct Rectangle Rectangle;

Rectangle * createRectangle(void);

Rectangle * createRectangle2(Point p);

Rectangle * createRectangle3(int w, int h);

Rectangle * createRectangle4(Point p, int w, int h);

void move(Rectangle *r, int x, int y);

int getArea(const Rectangle *r);

#endif