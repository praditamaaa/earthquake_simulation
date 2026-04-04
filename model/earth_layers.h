#ifndef EARTH_LAYERS_H
#define EARTH_LAYERS_H

#include <raylib.h>

/* File: model/earth_layers.h */

typedef struct {
    int   y_top;         /* y awal lapisan */
    int   thickness;     /* ketebalan dalam piksel */
    Color color;
    const char *name;
} EarthLayer;

#define NUM_EARTH_LAYERS 4

extern const EarthLayer DEFAULT_LAYERS[NUM_EARTH_LAYERS];

void EarthLayers_DrawLeft(const EarthLayer *layers, int n,
                          int x_start, int x_end,
                          float offset_x, float offset_y);
void EarthLayers_DrawRight(const EarthLayer *layers, int n,
                           int x_start, int x_end,
                           float offset_x, float offset_y);

#endif /* EARTH_LAYERS_H */
