/* File: view/earthquake_view.c */
#include "earthquake_view.h"
#include "earth_layers.h"
#include "element_view.h"
#include "framebuffer.h"
#include "matrix3x3.h"
#include "polygon_fill.h"
#include "raylib.h"
#include "earthquake_model.h"
#include "transforms.h"
#include "bresenham.h"
#include "hud_view.h"
#include "scene_view.h"
#include <math.h>
#include <stdlib.h>

static void Draw_PlateCracks(Mat3 transform, float x_start, float x_end, float y_top) {
  int seed = (int)x_start;
  srand(seed);
  int count = 10; // More cracks
  for (int i = 0; i < count; i++) {
    float cx = x_start + (x_end - x_start) * ((float)rand() / RAND_MAX);
    float cy = y_top;
    Vec2 p[3] = {
        {cx, cy},
        {cx + (rand() % 40 - 20), cy + 25},
        {cx + (rand() % 40 - 20), cy + 55}};

    Vec2 tp[3];
    Mat3_ApplyPolygon(transform, p, tp, 3);

    // Draw 3 times with slight offset for "Thick" effect
    for (int off = -1; off <= 1; off++) {
      Bres_Line((int)tp[0].x + off, (int)tp[0].y, (int)tp[1].x + off, (int)tp[1].y, DARKBROWN);
      Bres_Line((int)tp[1].x + off, (int)tp[1].y, (int)tp[2].x + off, (int)tp[2].y, DARKBROWN);
    }
  }
}

static void Draw_SoilDebris(Mat3 transform, float x, float y) {
    // Random small triangles as debris
    for (int i = 0; i < 3; i++) {
        float dx = (float)(rand() % 40 - 20);
        float dy = (float)(rand() % 20 - 10);
        Vec2 tri[3] = {
            {x + dx, y + dy},
            {x + dx + 10, y + dy + 5},
            {x + dx + 5, y + dy + 12}
        };
        Vec2 t_tri[3];
        Mat3_ApplyPolygon(transform, tri, t_tri, 3);
        Poly_Fill(t_tri, 3, (Color){100, 70, 50, 255}); // Soil color
    }
}

static void EarthquakeView_DrawPlates(const EarthquakeModel *m, float offset_x, float offset_y) {
  float split_x = 400.0f;
  
  EarthLayers_DrawLeft(DEFAULT_LAYERS, NUM_EARTH_LAYERS-1, -200, (int)split_x, 
                       m->left_plate_offset_x + offset_x, offset_y);
  
  if (m->phase >= EQ_PHASE_TREMOR) {
      Mat3 t_left;
      Trans_Translate(m->left_plate_offset_x + offset_x, offset_y, &t_left);
      Draw_PlateCracks(t_left, 50.0f, split_x - 50, (float)DEFAULT_LAYERS[0].y_top);
      if (m->phase == EQ_PHASE_TREMOR) Draw_SoilDebris(t_left, split_x - 30, (float)DEFAULT_LAYERS[0].y_top);
  }

  // Right Plate (Extended x_end to SCREEN_W + 400 to prevent gaps)
  EarthLayers_DrawRight(DEFAULT_LAYERS, NUM_EARTH_LAYERS-1, (int)split_x, SCREEN_W + 400, 
                        m->right_plate_offset_x + offset_x, offset_y);

  if (m->phase >= EQ_PHASE_TREMOR) {
      Mat3 t_right;
      Trans_Translate(m->right_plate_offset_x + offset_x, offset_y, &t_right);
      Draw_PlateCracks(t_right, split_x + 50, (float)SCREEN_W - 50, (float)DEFAULT_LAYERS[0].y_top);
      if (m->phase == EQ_PHASE_TREMOR) {
          srand((int)(m->phase_timer * 100));
          Draw_SoilDebris(t_right, split_x + (float)(rand()%100), (float)DEFAULT_LAYERS[0].y_top);
      }
  }

  /* 3. Static Lava Layer (Drawn last to cover the extended plate parts) */
  const EarthLayer *lava_layer = &DEFAULT_LAYERS[NUM_EARTH_LAYERS - 1];
  Vec2 lava_pts[4] = {
      {0.0f, (float)lava_layer->y_top},
      {(float)SCREEN_W, (float)lava_layer->y_top},
      {(float)SCREEN_W, (float)SCREEN_H},
      {0.0f, (float)SCREEN_H}};
  Poly_Fill(lava_pts, 4, lava_layer->color);
}

static void EarthquakeView_DrawStructures(const EarthquakeModel *m, float offset_x, float offset_y) {
  float ground_y = 300.0f;
  Color wall = {220, 220, 220, 255};
  Color roof = {180, 60, 60, 255};
  
  static const float pos_x[16] = {
    40, 95, 150,   
    200, 270,
    380, 460, 540, 620, 700, 780,
    890, 960, 
    1070, 1125, 1180
  };
  static const int is_building[16] = {2,2,2, 3,3, 1,1,1,1,1,1, 3,3, 2,2,2};

  for (int i = 0; i < 16; i++) {
    float x = pos_x[i];
    float plate_off_x = (x < 400) ? m->left_plate_offset_x : m->right_plate_offset_x;
    
    float draw_x = x + plate_off_x + offset_x;
    float draw_y = ground_y + offset_y; // Purely horizontal (ignore subduction/uplift)
    
    Mat3 t;
    Trans_Translate(draw_x, draw_y, &t);
    
    if (is_building[i] == 1) {
      Draw_DetailedBuilding(t, 60, 180, wall, roof, m->building_damaged[i]);
    } else if (is_building[i] == 2) {
      Draw_SimpleHouse(t, 50, 40, wall, roof, m->building_damaged[i]);
    } else if (is_building[i] == 3) {
      Draw_Building2(t, 30, 200, wall, roof, m->building_damaged[i]);
    } else {
      continue;
    }
  }
}

void EarthquakeView_Draw(const AppState *state) {
  const EarthquakeModel *m = &state->earthquake_model;

  SceneView_DrawSky(SCREEN_H, (Color){190, 230, 250, 255});

  Draw_BoldSun(100, 100, 40);
  
  // Clouds with horizontal movement
  float cw = (float)SCREEN_W + 200.0f;
  float c_off = m->cloud_timer;
  
  Draw_FluffyCloud((int)fmodf(250 + c_off, cw) - 100, 80, 100);
  Draw_FluffyCloud((int)fmodf(500 + c_off, cw) - 100, 100, 110);
  Draw_FluffyCloud((int)fmodf(750 + c_off, cw) - 100, 80, 100);
  Draw_FluffyCloud((int)fmodf(1000 + c_off, cw) - 100, 110, 120);

  EarthquakeView_DrawPlates(m, m->shake_x_offset, m->shake_y_offset);
  EarthquakeView_DrawStructures(m, m->shake_x_offset, m->shake_y_offset);
  
  HudView_DrawIntensitySlider(m->intensity);
  
  if (m->phase == EQ_PHASE_DONE) {
      DrawText("SIMULASI SELESAI", SCREEN_W/2 - 120, SCREEN_H/2 - 40, 30, YELLOW);
      DrawText("Tekan [R] untuk Restart | [Backspace] kembali ke Menu", SCREEN_W/2 - 250, SCREEN_H/2 + 10, 20, WHITE);
  }
}