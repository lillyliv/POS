#pragma once
#include <X11/Xlib.h>
#include <vector>

unsigned int screenWidth = 0;
unsigned int screenHeight = 0;

typedef enum PRIMITIVES {
    PRIM_LINE,
    PRIM_TRI,
    PRIM_RECT,
    PRIM_CIRCLE
} PRIMITIVES;

typedef struct {
    PRIMITIVES PRIM;
    unsigned int x;
    unsigned int y;
    unsigned int circle_radius;
    unsigned int x2; // x2, y2, for lines and triangles
    unsigned int y2;
    unsigned int x3; // x3, y3, for triangles
    unsigned int y3;
    unsigned int w;
    unsigned int h;
    XColor color;
} SHAPE;

std::vector<SHAPE> shapesVector; // loops through this every frame and draws all the shapes
