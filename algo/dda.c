/* File: algo/dda.c */
#include "dda.h"
#include "framebuffer.h"
#include <math.h>
#include <stdlib.h>

void DDA_Line(int x0, int y0, int x1, int y1, Color col) {
    int dx = x1 - x0;
    int dy = y1 - y0;
    int steps = (abs(dx) > abs(dy)) ? abs(dx) : abs(dy);
    
    if (steps == 0) {
        FB_SetPixel(x0, y0, col);
        return;
    }
    
    float x_inc = (float)dx / (float)steps;
    float y_inc = (float)dy / (float)steps;
    
    float x = (float)x0;
    float y = (float)y0;
    
    for (int i = 0; i <= steps; i++) {
        FB_SetPixel((int)roundf(x), (int)roundf(y), col);
        x += x_inc;
        y += y_inc;
    }
}

void DDA_ThickLine(int x0, int y0, int x1, int y1, int thickness, Color col) {
    int dx = x1 - x0;
    int dy = y1 - y0;
    
    if (abs(dx) > abs(dy)) {
        for (int i = -thickness / 2; i <= thickness / 2; i++) {
            DDA_Line(x0, y0 + i, x1, y1 + i, col);
        }
    } else {
        for (int i = -thickness / 2; i <= thickness / 2; i++) {
            DDA_Line(x0 + i, y0, x1 + i, y1, col);
        }
    }
}

void DDA_DashedLine(int x0, int y0, int x1, int y1, int dash_len, Color col) {
    int dx = x1 - x0;
    int dy = y1 - y0;
    int steps = (abs(dx) > abs(dy)) ? abs(dx) : abs(dy);
    
    if (steps == 0) {
        FB_SetPixel(x0, y0, col);
        return;
    }
    
    float x_inc = (float)dx / (float)steps;
    float y_inc = (float)dy / (float)steps;
    
    float x = (float)x0;
    float y = (float)y0;
    
    int draw = 1;
    for (int i = 0; i <= steps; i++) {
        if (draw) FB_SetPixel((int)roundf(x), (int)roundf(y), col);
        if ((i + 1) % dash_len == 0) draw = !draw;
        x += x_inc;
        y += y_inc;
    }
}
