#ifndef DDA_H
#define DDA_H

#include <raylib.h>

/* File: algo/dda.h */

void DDA_Line(int x0, int y0, int x1, int y1, Color col);
void DDA_ThickLine(int x0, int y0, int x1, int y1, int thickness, Color col);
void DDA_DashedLine(int x0, int y0, int x1, int y1, int dash_len, Color col);

#endif /* DDA_H */
