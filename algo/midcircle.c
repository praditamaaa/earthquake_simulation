/* File: algo/midcircle.c */
#include "midcircle.h"
#include "framebuffer.h"

static void DrawCirclePoints(int cx, int cy, int x, int y, Color col) {
    FB_SetPixel(cx + x, cy + y, col);
    FB_SetPixel(cx - x, cy + y, col);
    FB_SetPixel(cx + x, cy - y, col);
    FB_SetPixel(cx - x, cy - y, col);
    FB_SetPixel(cx + y, cy + x, col);
    FB_SetPixel(cx - y, cy + x, col);
    FB_SetPixel(cx + y, cy - x, col);
    FB_SetPixel(cx - y, cy - x, col);
}

void MC_Circle(int cx, int cy, int r, Color col) {
    if (r < 0) return;
    int x = 0;
    int y = r;
    int p = 1 - r;

    DrawCirclePoints(cx, cy, x, y, col);

    while (x < y) {
        x++;
        if (p < 0) {
            p += 2 * x + 1;
        } else {
            y--;
            p += 2 * (x - y) + 1;
        }
        DrawCirclePoints(cx, cy, x, y, col);
    }
}

static void MC_Circle_HorizontalScanlines(int cx, int cy, int x, int y, Color col) {
    for (int i = cx - x; i <= cx + x; i++) {
        FB_SetPixel(i, cy + y, col);
        FB_SetPixel(i, cy - y, col);
    }
    for (int i = cx - y; i <= cx + y; i++) {
        FB_SetPixel(i, cy + x, col);
        FB_SetPixel(i, cy - x, col);
    }
}

void MC_CircleFilled(int cx, int cy, int r, Color col) {
    if (r < 0) return;
    int x = 0;
    int y = r;
    int p = 1 - r;

    MC_Circle_HorizontalScanlines(cx, cy, x, y, col);

    while (x < y) {
        x++;
        if (p < 0) {
            p += 2 * x + 1;
        } else {
            y--;
            p += 2 * (x - y) + 1;
        }
        MC_Circle_HorizontalScanlines(cx, cy, x, y, col);
    }
}
