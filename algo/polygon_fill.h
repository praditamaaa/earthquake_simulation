#ifndef POLYGON_FILL_H
#define POLYGON_FILL_H

#include <raylib.h>
#include "matrix3x3.h"

/* File: algo/polygon_fill.h */

#define MAX_POLY_VERTS  32
#define MAX_SCANLINE_INTERSECTIONS 16

void Poly_Fill(const Vec2 *verts, int n, Color col);
void Poly_Outline(const Vec2 *verts, int n, Color col);
void Poly_FillAndOutline(const Vec2 *verts, int n, Color fill_col, Color outline_col);

void Poly_FillTransformed(const Vec2 *verts, int n, Mat3 transform, Color col);
void Poly_OutlineTransformed(const Vec2 *verts, int n, Mat3 transform, Color col);
void Poly_FillAndOutlineTransformed(const Vec2 *verts, int n, Mat3 transform, Color fill_col, Color outline_col);

#endif /* POLYGON_FILL_H */
