/* File: view/hud_view.c */
#include "hud_view.h"
#include "dda.h"
#include "framebuffer.h"

static void DrawRectFill(int x, int y, int w, int h, Color col) {
    for (int i = 0; i < h; i++) {
        DDA_Line(x, y + i, x + w, y + i, col);
    }
}

void HudView_DrawInfo(const char *scenario_name,
                      const char *phase_name,
                      float phase_progress,
                      int paused,
                      int show_debug) {
    /* Panel info atas */
    DrawRectFill(0, 0, SCREEN_W, 40, (Color){0, 0, 0, 180});
    DDA_Line(0, 40, SCREEN_W, 40, WHITE);
    
    DrawText(scenario_name, 20, 10, 20, WHITE);
    DrawText(phase_name, 300, 10, 20, LIGHTGRAY);
    
    /* Progress bar phase */
    int prog_w = 400;
    DrawRectFill(SCREEN_W - prog_w - 20, 18, prog_w, 4, DARKGRAY);
    DrawRectFill(SCREEN_W - prog_w - 20, 18, (int)(prog_w * phase_progress), 4, WHITE);
    
    /* Label kontrol */
    DrawRectFill(0, SCREEN_H - 40, SCREEN_W, 40, (Color){0, 0, 0, 180});
    DrawText("SPACE=pause  R=restart  BACKSPACE=menu  F1=skip phase  F2=debug", 20, SCREEN_H - 30, 20, WHITE);
    
    if (paused) {
        int pw = MeasureText("PAUSED", 40);
        DrawText("PAUSED", SCREEN_W/2 - pw/2, SCREEN_H/2 - 20, 40, RED);
    }
    
    if (show_debug) {
        DrawText(TextFormat("FPS: %d", GetFPS()), 20, 60, 20, GREEN);
    }
}

void HudView_DrawIntensitySlider(float intensity) {
    int sx = SCREEN_W / 2 - 100, sy = SCREEN_H - 80, sw = 200, sh = 20;
    
    /* Background bar */
    DrawRectFill(sx, sy, sw, sh, DARKGRAY);
    
    /* Progress fill (0.5 to 2.0 mapped to 0 to 1) */
    float norm = (intensity - 0.5f) / 1.5f;
    if (norm < 0) norm = 0;
    if (norm > 1) norm = 1;
    
    DrawRectFill(sx, sy, (int)(sw * norm), sh, MAROON);
    
    /* Outline */
    DDA_Line(sx, sy, sx + sw, sy, WHITE);
    DDA_Line(sx, sy + sh, sx + sw, sy + sh, WHITE);
    DDA_Line(sx, sy, sx, sy + sh, WHITE);
    DDA_Line(sx + sw, sy, sx + sw, sy + sh, WHITE);
    
    /* Handle */
    int hx = sx + (int)(sw * norm);
    DrawRectFill(hx - 4, sy - 2, 8, sh + 4, WHITE);
    
    DrawText(TextFormat("Intensity: %.1fx", intensity), sx + sw + 10, sy, 20, WHITE);
}
