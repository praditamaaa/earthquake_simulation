/* File: core/color_utils.c */
#include "color_utils.h"

Color CU_ColorLerp(Color a, Color b, float t) {
    if (t < 0.0f) t = 0.0f;
    if (t > 1.0f) t = 1.0f;
    return (Color){
        (unsigned char)(a.r + (b.r - a.r) * t),
        (unsigned char)(a.g + (b.g - a.g) * t),
        (unsigned char)(a.b + (b.b - a.b) * t),
        (unsigned char)(a.a + (b.a - a.a) * t)
    };
}

Color CU_ColorAlpha(Color c, float alpha) {
    if (alpha < 0.0f) alpha = 0.0f;
    if (alpha > 1.0f) alpha = 1.0f;
    unsigned char a = (unsigned char)(c.a * alpha);
    return (Color){ c.r, c.g, c.b, a };
}
