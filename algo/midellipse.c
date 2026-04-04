/* File: algo/midellipse.c */
#include "midellipse.h"
#include "framebuffer.h"

static void DrawEllipsePoints(int cx, int cy, int x, int y, Color col) {
    FB_SetPixel(cx + x, cy + y, col);
    FB_SetPixel(cx - x, cy + y, col);
    FB_SetPixel(cx + x, cy - y, col);
    FB_SetPixel(cx - x, cy - y, col);
}

void ME_Ellipse(int cx, int cy, int rx, int ry, Color col) {
    if (rx == 0 || ry == 0) return;
    int x = 0;
    int y = ry;
    long rx2 = rx * rx;
    long ry2 = ry * ry;
    long twory2 = 2 * ry2;
    long tworx2 = 2 * rx2;
    long px = 0;
    long py = tworx2 * y;

    /* Region 1 */
    long p1 = ry2 - (rx2 * ry) + (0.25f * rx2);
    while (px < py) {
        DrawEllipsePoints(cx, cy, x, y, col);
        x++;
        px += twory2;
        if (p1 < 0) {
            p1 += ry2 + px;
        } else {
            y--;
            py -= tworx2;
            p1 += ry2 + px - py;
        }
    }

    /* Region 2 */
    long p2 = ry2 * (x + 0.5f) * (x + 0.5f) + rx2 * (y - 1) * (y - 1) - rx2 * ry2;
    while (y >= 0) {
        DrawEllipsePoints(cx, cy, x, y, col);
        y--;
        py -= tworx2;
        if (p2 > 0) {
            p2 += rx2 - py;
        } else {
            x++;
            px += twory2;
            p2 += rx2 - py + px;
        }
    }
}

static void ME_Ellipse_HorizontalScanlines(int cx, int cy, int x, int y, Color col) {
    for (int i = cx - x; i <= cx + x; i++) {
        FB_SetPixel(i, cy + y, col);
        FB_SetPixel(i, cy - y, col);
    }
}

void ME_EllipseFilled(int cx, int cy, int rx, int ry, Color col) {
    if (rx == 0 || ry == 0) return;
    int x = 0;
    int y = ry;
    long rx2 = rx * rx;
    long ry2 = ry * ry;
    long twory2 = 2 * ry2;
    long tworx2 = 2 * rx2;
    long px = 0;
    long py = tworx2 * y;

    long p1 = ry2 - (rx2 * ry) + (0.25f * rx2);
    while (px < py) {
        ME_Ellipse_HorizontalScanlines(cx, cy, x, y, col);
        x++;
        px += twory2;
        if (p1 < 0) {
            p1 += ry2 + px;
        } else {
            y--;
            py -= tworx2;
            p1 += ry2 + px - py;
        }
    }

    long p2 = ry2 * (x + 0.5f) * (x + 0.5f) + rx2 * (y - 1) * (y - 1) - rx2 * ry2;
    while (y >= 0) {
        ME_Ellipse_HorizontalScanlines(cx, cy, x, y, col);
        y--;
        py -= tworx2;
        if (p2 > 0) {
            p2 += rx2 - py;
        } else {
            x++;
            px += twory2;
            p2 += rx2 - py + px;
        }
    }
}
