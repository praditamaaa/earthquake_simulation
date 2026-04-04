/* File: model/earth_layers.c */
#include "earth_layers.h"
#include "polygon_fill.h"
#include "transforms.h"
#include "dda.h"

const EarthLayer DEFAULT_LAYERS[NUM_EARTH_LAYERS] = {
    {300, 20,  {34, 177, 76, 255}, "Grass"},      /* Green top */
    {320, 60,  {40, 40, 40, 255}, "Dark Soil"},   /* Black/Gray middle */
    {380, 260, {84, 52, 29, 255}, "Deep Crust"},  /* Brown bottom */
    {640, 80,  {255, 69, 0, 255}, "Lava"},        /* Red/Orange lava */
};

void EarthLayers_DrawLeft(const EarthLayer *layers, int n,
                          int x_start, int x_end,
                          float offset_x, float offset_y) {
    for (int i = 0; i < n; i++) {
        const EarthLayer *layer = &layers[i];
        
        Vec2 verts[4];
        verts[0].x = x_start; verts[0].y = (float)layer->y_top;
        verts[1].x = x_end;   verts[1].y = (float)layer->y_top;
        verts[2].x = x_end;   verts[2].y = (float)(layer->y_top + layer->thickness);
        verts[3].x = x_start; verts[3].y = (float)(layer->y_top + layer->thickness);
        
        Mat3 transform;
        Trans_Translate(offset_x, offset_y, &transform);
        
        Poly_FillTransformed(verts, 4, transform, layer->color);
        
        if (i > 0) {
            Vec2 line[2] = {verts[0], verts[1]};
            Vec2 t_line[2];
            Mat3_ApplyPolygon(transform, line, t_line, 2);
            DDA_DashedLine((int)t_line[0].x, (int)t_line[0].y, 
                           (int)t_line[1].x, (int)t_line[1].y, 10, DARKBROWN);
        }
    }
}

void EarthLayers_DrawRight(const EarthLayer *layers, int n,
                           int x_start, int x_end,
                           float offset_x, float offset_y) {
    for (int i = 0; i < n; i++) {
        const EarthLayer *layer = &layers[i];
        
        Vec2 verts[4];
        verts[0].x = x_start; verts[0].y = (float)layer->y_top;
        verts[1].x = x_end;   verts[1].y = (float)layer->y_top;
        verts[2].x = x_end;   verts[2].y = (float)(layer->y_top + layer->thickness);
        verts[3].x = x_start; verts[3].y = (float)(layer->y_top + layer->thickness);
        
        Mat3 transform;
        Trans_Translate(offset_x, offset_y, &transform);
        
        Poly_FillTransformed(verts, 4, transform, layer->color);
        
        if (i > 0) {
            Vec2 line[2] = {verts[0], verts[1]};
            Vec2 t_line[2];
            Mat3_ApplyPolygon(transform, line, t_line, 2);
            DDA_DashedLine((int)t_line[0].x, (int)t_line[0].y, 
                           (int)t_line[1].x, (int)t_line[1].y, 10, DARKBROWN);
        }
    }
}
