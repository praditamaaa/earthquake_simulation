/* File: algo/polygon_fill.c */
#include "polygon_fill.h"
#include "dda.h"
#include "framebuffer.h"
#include "app_state.h"
#include <stdlib.h>
#include <math.h>

static int CompareInts(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

void Poly_Fill(const Vec2 *verts, int n, Color col) {
    if (n < 3) return;

    float min_y = verts[0].y, max_y = verts[0].y;
    for (int i = 1; i < n; i++) {
        if (verts[i].y < min_y) min_y = verts[i].y;
        if (verts[i].y > max_y) max_y = verts[i].y;
    }

    int y_start = (int)ceilf(min_y);
    int y_end = (int)floorf(max_y);
    
    if (y_start < 0) y_start = 0;
    if (y_end >= SCREEN_H) y_end = SCREEN_H - 1;

    for (int y = y_start; y <= y_end; y++) {
        int intersections[MAX_SCANLINE_INTERSECTIONS];
        int count = 0;

        for (int i = 0; i < n; i++) {
            int j = (i + 1) % n;
            float y1 = verts[i].y, y2 = verts[j].y;
            float x1 = verts[i].x, x2 = verts[j].x;

            if ((y1 <= y && y2 > y) || (y2 <= y && y1 > y)) {
                if (y1 != y2) {
                    float x_int = x1 + (y - y1) * (x2 - x1) / (y2 - y1);
                    if (count < MAX_SCANLINE_INTERSECTIONS) {
                        intersections[count++] = (int)roundf(x_int);
                    }
                }
            }
        }

        qsort(intersections, count, sizeof(int), CompareInts);

        for (int i = 0; i < count; i += 2) {
            if (i + 1 < count) {
                int x_start = intersections[i];
                int x_end = intersections[i + 1];
                
                if (x_start < 0) x_start = 0;
                if (x_end >= SCREEN_W) x_end = SCREEN_W - 1;

                for (int x = x_start; x <= x_end; x++) {
                    FB_SetPixel(x, y, col);
                }
            }
        }
    }
}

void Poly_Outline(const Vec2 *verts, int n, Color col) {
    if (n < 2) return;
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        DDA_Line((int)roundf(verts[i].x), (int)roundf(verts[i].y),
                 (int)roundf(verts[j].x), (int)roundf(verts[j].y), col);
    }
}

void Poly_FillAndOutline(const Vec2 *verts, int n, Color fill_col, Color outline_col) {
    Poly_Fill(verts, n, fill_col);
    Poly_Outline(verts, n, outline_col);
}

void Poly_FillTransformed(const Vec2 *verts, int n, Mat3 transform, Color col) {
    if (n < 3) return;
    Vec2 t_verts[MAX_POLY_VERTS];
    int count = (n > MAX_POLY_VERTS) ? MAX_POLY_VERTS : n;
    Mat3_ApplyPolygon(transform, verts, t_verts, count);
    Poly_Fill(t_verts, count, col);
}

void Poly_OutlineTransformed(const Vec2 *verts, int n, Mat3 transform, Color col) {
    if (n < 2) return;
    Vec2 t_verts[MAX_POLY_VERTS];
    int count = (n > MAX_POLY_VERTS) ? MAX_POLY_VERTS : n;
    Mat3_ApplyPolygon(transform, verts, t_verts, count);
    Poly_Outline(t_verts, count, col);
}

void Poly_FillAndOutlineTransformed(const Vec2 *verts, int n, Mat3 transform, Color fill_col, Color outline_col) {
    if (n < 3) return;
    Vec2 t_verts[MAX_POLY_VERTS];
    int count = (n > MAX_POLY_VERTS) ? MAX_POLY_VERTS : n;
    Mat3_ApplyPolygon(transform, verts, t_verts, count);
    Poly_FillAndOutline(t_verts, count, fill_col, outline_col);
}
