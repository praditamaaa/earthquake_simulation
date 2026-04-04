/* File: view/scene_view.c */
#include "scene_view.h"
#include "app_state.h"
#include "polygon_fill.h"
#include "midcircle.h"
#include "midellipse.h"
#include "dda.h"
#include "framebuffer.h"
#include <math.h>

const BuildingDef DEFAULT_BUILDINGS[6] = {
    {80,  200, 55, 110, 5, {160,155,150,255}, {120,50,40,255}, {180,210,240,200}},
    {155, 200, 45,  90, 4, {155,150,145,255}, {115,45,35,255}, {180,210,240,200}},
    {350, 200, 50, 120, 5, {165,160,155,255}, {125,55,45,255}, {180,210,240,200}},
    {850, 200, 60, 100, 4, {160,155,150,255}, {120,50,40,255}, {180,210,240,200}},
    {930, 200, 50, 130, 5, {155,150,145,255}, {115,45,35,255}, {180,210,240,200}},
    {1100,200, 55,  95, 4, {165,160,155,255}, {125,55,45,255}, {180,210,240,200}},
};

void SceneView_DrawSky(int screen_h_limit, Color sky_color) {
    Vec2 verts[4] = {
        {0, 0},
        {SCREEN_W, 0},
        {SCREEN_W, screen_h_limit},
        {0, screen_h_limit}
    };
    Poly_Fill(verts, 4, sky_color);
}

void SceneView_DrawSun(int cx, int cy, int r) {
    MC_CircleFilled(cx, cy, r, YELLOW);
    
    for (int angle = 0; angle <= 330; angle += 30) {
        float rad = angle * PI / 180.0f;
        int x0 = cx + (int)roundf((r + 5) * cosf(rad));
        int y0 = cy + (int)roundf((r + 5) * sinf(rad));
        int x1 = cx + (int)roundf((r + 25) * cosf(rad));
        int y1 = cy + (int)roundf((r + 25) * sinf(rad));
        DDA_ThickLine(x0, y0, x1, y1, 3, YELLOW);
    }
}

void SceneView_DrawEarthLayersLeft(const EarthLayer *layers, int n,
                                   int x_end, float off_x, float off_y) {
    EarthLayers_DrawLeft(layers, n, 0, x_end, off_x, off_y);
}

void SceneView_DrawEarthLayersRight(const EarthLayer *layers, int n,
                                    int x_start, float off_x, float off_y) {
    EarthLayers_DrawRight(layers, n, x_start, SCREEN_W, off_x, off_y);
}

void SceneView_DrawRiftGap(float rift_x, float rift_width,
                           int y_top, int y_bottom, Color gap_color) {
    if (rift_width <= 0.0f) return;
    Vec2 verts[4] = {
        {rift_x - rift_width / 2.0f, y_top},
        {rift_x + rift_width / 2.0f, y_top},
        {rift_x + rift_width / 2.0f, y_bottom},
        {rift_x - rift_width / 2.0f, y_bottom}
    };
    Poly_Fill(verts, 4, gap_color);
}

void SceneView_DrawParticles(const ParticleSystem *ps) {
    for (int i = 0; i < MAX_PARTICLES; i++) {
        if (ps->pool[i].active) {
            int px = (int)roundf(ps->pool[i].x);
            int py = (int)roundf(ps->pool[i].y);
            int r = (int)roundf(ps->pool[i].radius);
            Color col = ps->pool[i].color;
            
            /* Fade out particle based on life */
            float life_ratio = ps->pool[i].life / ps->pool[i].max_life;
            col.a = (unsigned char)(col.a * life_ratio);
            
            if (ps->pool[i].type == PARTICLE_DUST || ps->pool[i].type == PARTICLE_SMOKE) {
                ME_EllipseFilled(px, py, r + 2, r, col);
            } else {
                MC_CircleFilled(px, py, r, col);
            }
        }
    }
}
