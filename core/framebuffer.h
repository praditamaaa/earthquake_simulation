#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <raylib.h>

#define SCREEN_W 1280
#define SCREEN_H 720

/* File: core/framebuffer.h */
/* Set pixel safely within screen bounds */
static inline void FB_SetPixel(int x, int y, Color col) {
    if (x >= 0 && x < SCREEN_W && y >= 0 && y < SCREEN_H) {
        DrawPixel(x, y, col);
    }
}

#endif /* FRAMEBUFFER_H */
