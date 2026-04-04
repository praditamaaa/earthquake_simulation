/* File: algo/bresenham.c */
#include "bresenham.h"
#include "framebuffer.h"
#include <stdlib.h>

void Bres_Line(int x0, int y0, int x1, int y1, Color col) {
    int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1; 
    int err = dx + dy, e2;
 
    while (1) {
        FB_SetPixel(x0, y0, col);
        if (x0 == x1 && y0 == y1) break;
        e2 = 2 * err;
        if (e2 >= dy) { err += dy; x0 += sx; }
        if (e2 <= dx) { err += dx; y0 += sy; }
    }
}

void Bres_ThickLine(int x0, int y0, int x1, int y1, int thickness, Color col) {
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    
    if (dx > dy) {
        for (int i = -thickness / 2; i <= thickness / 2; i++) {
            Bres_Line(x0, y0 + i, x1, y1 + i, col);
        }
    } else {
        for (int i = -thickness / 2; i <= thickness / 2; i++) {
            Bres_Line(x0 + i, y0, x1 + i, y1, col);
        }
    }
}

void Bres_DashedLine(int x0, int y0, int x1, int y1, int dash_len, Color col) {
    int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1; 
    int err = dx + dy, e2;
    int count = 0;
    int draw = 1;
 
    while (1) {
        if (draw) FB_SetPixel(x0, y0, col);
        count++;
        if (count == dash_len) {
            draw = !draw;
            count = 0;
        }
        if (x0 == x1 && y0 == y1) break;
        e2 = 2 * err;
        if (e2 >= dy) { err += dy; x0 += sx; }
        if (e2 <= dx) { err += dx; y0 += sy; }
    }
}
