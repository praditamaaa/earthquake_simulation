#ifndef COLOR_UTILS_H
#define COLOR_UTILS_H

#include <raylib.h>

/* File: core/color_utils.h */

Color CU_ColorLerp(Color a, Color b, float t);
Color CU_ColorAlpha(Color c, float alpha);

/* Palette warna proyek */
#define COL_SKY          (Color){100, 170, 220, 255}
#define COL_GROUND_SURF  (Color){80,  120, 50,  255}
#define COL_CRUST        (Color){110, 85,  55,  255}
#define COL_UPPER_MANTLE (Color){90,  60,  35,  255}
#define COL_LOWER_MANTLE (Color){75,  45,  25,  255}
#define COL_MAGMA_ROOM   (Color){200, 60,  20,  255}
#define COL_OUTER_CORE   (Color){180, 30,  10,  255}
#define COL_INNER_CORE   (Color){140, 15,  5,   255}
#define COL_LAVA_HOT     (Color){255, 80,  0,   255}
#define COL_LAVA_COOL    (Color){180, 40,  0,   255}
#define COL_ASH          (Color){120, 110, 100, 200}
#define COL_BUILDING     (Color){160, 155, 150, 255}
#define COL_ROOF         (Color){120, 50,  40,  255}
#define COL_CRACK        (Color){40,  30,  20,  255}
#define COL_MAGMA_ACTIVE (Color){220, 80,  10,  255}
#define COL_NEW_CRUST    (Color){60,  40,  25,  255}
#define COL_CONDUIT      (Color){190, 50,  15,  255}
#define COL_VOLCANO_BODY (Color){70,  55,  45,  255}

#endif /* COLOR_UTILS_H */
