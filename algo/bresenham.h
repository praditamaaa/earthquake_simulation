#ifndef BRESENHAM_H
#define BRESENHAM_H

#include <raylib.h>

/* File: algo/bresenham.h */

void Bres_Line(int x0, int y0, int x1, int y1, Color col);
void Bres_ThickLine(int x0, int y0, int x1, int y1, int thickness, Color col);
void Bres_DashedLine(int x0, int y0, int x1, int y1, int dash_len, Color col);

#endif /* BRESENHAM_H */
