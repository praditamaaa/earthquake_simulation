#ifndef SCENE_VIEW_H
#define SCENE_VIEW_H

#include <raylib.h>
#include "earth_layers.h"
#include "particle_model.h"

/* File: view/scene_view.h */

typedef struct {
    float x, y;          /* pojok kiri-bawah */
    float width;
    float height;
    int   floors;
    Color wall_color;
    Color roof_color;
    Color window_color;
} BuildingDef;

extern const BuildingDef DEFAULT_BUILDINGS[6];

void SceneView_DrawSky(int screen_h_limit, Color sky_color);
void SceneView_DrawSun(int cx, int cy, int r);
void SceneView_DrawEarthLayersLeft(const EarthLayer *layers, int n,
                                   int x_end, float off_x, float off_y);
void SceneView_DrawEarthLayersRight(const EarthLayer *layers, int n,
                                    int x_start, float off_x, float off_y);
void SceneView_DrawRiftGap(float rift_x, float rift_width,
                           int y_top, int y_bottom, Color gap_color);
void SceneView_DrawParticles(const ParticleSystem *ps);

#endif /* SCENE_VIEW_H */
