/* File: view/common/element_view.c */
#include "element_view.h"
#include "midcircle.h"
#include "polygon_fill.h"
#include "bresenham.h"
#include "dda.h"
#include "transforms.h"
#include "matrix3x3.h"
#include <math.h>
#include <stdlib.h>

#define PI 3.14159265358979323846f

void Draw_BoldSun(int cx, int cy, int r) {
    /* 1. Core (Yellow Circle) */
    MC_CircleFilled(cx, cy, r, YELLOW);
    
    /* 2. Rays (Yellow Lines) */
    int num_rays = 8;
    float angle_step = (2.0f * PI) / num_rays;
    float inner_r = r + 5.0f;
    float outer_r = r + 25.0f;
    
    for (int i = 0; i < num_rays; i++) {
        float angle = i * angle_step;
        int x1 = cx + (int)(cosf(angle) * inner_r);
        int y1 = cy + (int)(sinf(angle) * inner_r);
        int x2 = cx + (int)(cosf(angle) * outer_r);
        int y2 = cy + (int)(sinf(angle) * outer_r);
        Bres_Line(x1, y1, x2, y2, YELLOW);
    }
}

void Draw_FluffyCloud(int x, int y, int width) {
    /* 3 overlapping circles as per reference photo */
    int r_main = width / 3;
    int r_side = width / 4;
    
    MC_CircleFilled(x + width/2, y - r_main * 1.2f, r_main, WHITE); // Middle
    MC_CircleFilled(x + r_side, y - r_side, r_side, WHITE);       // Left
    MC_CircleFilled(x + width - r_side, y - r_side, r_side, WHITE); // Right
}

void Draw_DetailedBuilding(Mat3 transform, float w, float h, Color wall, Color roof, int state) {
    Color col_wall = { 160, 160, 160, 255 }; 
    Color col_win = WHITE;
    
    Mat3 final_trans = transform;
    if (state == 2) {
        Mat3 lean;
        Trans_Rotate(0.05f, &lean); // Leaning slightly
        Trans_Compose((Mat3[]){lean, transform}, 2, &final_trans);
    } else if (state == 3) {
        Mat3 lean;
        Trans_Rotate(0.1f, &lean); // Leaning more
        Trans_Compose((Mat3[]){lean, transform}, 2, &final_trans);
    }

    if (state < 4) {
        float effective_h = (state == 3) ? h * 0.6f : h; // Partially collapsed
        
        /* Building Body */
        Vec2 body[4] = {{0, -effective_h}, {w, -effective_h}, {w, 0}, {0, 0}};
        Poly_FillAndOutlineTransformed(body, 4, final_trans, col_wall, DARKGRAY);
        
        /* Windows */
        int rows = (state == 3) ? 2 : 4;
        int cols = 3;
        float win_s = w / 5.0f;
        float spacing_x = (w - (cols * win_s)) / (cols + 1);
        float spacing_y = (effective_h * 0.7f - (rows * win_s)) / (rows + 1);
        
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                float wx = spacing_x + c * (win_s + spacing_x);
                float wy = -effective_h + spacing_y + r * (win_s + spacing_y);
                Vec2 win[4] = {{wx, wy}, {wx + win_s, wy}, {wx + win_s, wy + win_s}, {wx, wy + win_s}};
                Poly_FillTransformed(win, 4, final_trans, col_win);
            }
        }
        
        /* Cracks */
        if (state >= 1) {
            Color crack_col = (state >= 2) ? BLACK : DARKGRAY;
            Vec2 c1[3] = {{w*0.2f, -effective_h*0.8f}, {w*0.5f, -effective_h*0.5f}, {w*0.3f, -effective_h*0.2f}};
            Vec2 tc1[3];
            Mat3_ApplyPolygon(final_trans, c1, tc1, 3);
            Bres_Line((int)tc1[0].x, (int)tc1[0].y, (int)tc1[1].x, (int)tc1[1].y, crack_col);
            Bres_Line((int)tc1[1].x, (int)tc1[1].y, (int)tc1[2].x, (int)tc1[2].y, crack_col);
            
            if (state >= 2) {
                Vec2 c2[3] = {{w*0.7f, -effective_h*0.9f}, {w*0.4f, -effective_h*0.6f}, {w*0.8f, -effective_h*0.3f}};
                Vec2 tc2[3];
                Mat3_ApplyPolygon(final_trans, c2, tc2, 3);
                Bres_Line((int)tc2[0].x, (int)tc2[0].y, (int)tc2[1].x, (int)tc2[1].y, crack_col);
                Bres_Line((int)tc2[1].x, (int)tc2[1].y, (int)tc2[2].x, (int)tc2[2].y, crack_col);
            }
        }
    } else {
        /* Fully Collapsed */
        Vec2 rubble[5] = {{ -w*0.3f, 0 }, { w*1.3f, 0 }, { w*1.0f, -h*0.2f }, { w*0.5f, -h*0.3f }, { -w*0.1f, -h*0.1f }};
        Poly_FillAndOutlineTransformed(rubble, 5, transform, col_wall, DARKGRAY);
    }
}

void Draw_SimpleHouse(Mat3 transform, float w, float h, Color wall, Color roof, int state) {
    Color col_wall = { 100, 100, 100, 255 }; 
    Color col_roof = BLACK;
    
    Mat3 final_trans = transform;
    if (state >= 2 && state < 4) {
        Mat3 lean;
        Trans_Rotate(0.08f, &lean);
        Trans_Compose((Mat3[]){lean, transform}, 2, &final_trans);
    }

    if (state < 4) {
        /* House Body */
        float effective_h = (state == 3) ? h * 0.5f : h;
        Vec2 body[4] = {{0, -effective_h}, {w, -effective_h}, {w, 0}, {0, 0}};
        Poly_FillAndOutlineTransformed(body, 4, final_trans, col_wall, DARKGRAY);
        
        /* Roof - Gone if state 3 */
        if (state < 3) {
            Vec2 roof_pts[4] = {{ -5, -h }, { w + 5, -h }, { w * 0.8f, -h - 15 }, { w * 0.2f, -h - 15 }};
            Poly_FillAndOutlineTransformed(roof_pts, 4, final_trans, col_roof, BLACK);
        }

        if (state >= 1) {
            Vec2 crack[3] = {{w*0.3f, -effective_h*0.7f}, {w*0.6f, -effective_h*0.4f}, {w*0.4f, -effective_h*0.2f}};
            Vec2 tc[3];
            Mat3_ApplyPolygon(final_trans, crack, tc, 3);
            Bres_Line((int)tc[0].x, (int)tc[0].y, (int)tc[1].x, (int)tc[1].y, BLACK);
            Bres_Line((int)tc[1].x, (int)tc[1].y, (int)tc[2].x, (int)tc[2].y, BLACK);
        }
    } else {
        /* Rubble */
        Vec2 rubble[4] = {{ -w*0.2f, 0 }, { w*1.2f, 0 }, { w*0.6f, -h*0.3f }, { 0, -h*0.1f }};
        Poly_FillAndOutlineTransformed(rubble, 4, transform, col_wall, DARKGRAY);
    }
}
