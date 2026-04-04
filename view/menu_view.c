/* File: view/menu_view.c */
#include "menu_view.h"
#include "dda.h"
#include "midcircle.h"
#include "framebuffer.h"
#include "color_utils.h"
#include <raylib.h>
#include <string.h>

static void DrawRectFill(int x, int y, int w, int h, Color col) {
    for (int i = 0; i < h; i++) {
        DDA_Line(x, y + i, x + w, y + i, col);
    }
}

static void DrawRectOutline(int x, int y, int w, int h, Color col) {
    DDA_Line(x, y, x + w, y, col);
    DDA_Line(x, y + h, x + w, y + h, col);
    DDA_Line(x, y, x, y + h, col);
    DDA_Line(x + w, y, x + w, y + h, col);
}

void MenuView_DrawMain(int selected_index) {
    /* Background Sky */
    DrawRectFill(0, 0, SCREEN_W, SCREEN_H, COL_SKY);
    
    /* Title */
    const char *title = "SIMULASI GEMPA TEKTONIK";
    int titleW = MeasureText(title, 40);
    DrawText(title, SCREEN_W/2 - titleW/2, 120, 40, WHITE);
    
    const char *subtitle = "Grafika Komputer - 241524023";
    int subW = MeasureText(subtitle, 20);
    DrawText(subtitle, SCREEN_W/2 - subW/2, 170, 20, LIGHTGRAY);
    
    /* Buttons */
    const char* labels[] = {
        "Mulai Simulasi",
        "Tentang Aplikasi",
        "Keluar"
    };
    
    int bw = 350;
    int bh = 55;
    int by = 280;
    
    for (int i = 0; i < 3; i++) {
        Color btn_col = (i == selected_index) ? GRAY : DARKGRAY;
        DrawRectFill(SCREEN_W/2 - bw/2, by + i*80, bw, bh, btn_col);
        DrawRectOutline(SCREEN_W/2 - bw/2, by + i*80, bw, bh, LIGHTGRAY);
        
        int textX = SCREEN_W/2 - MeasureText(labels[i], 24)/2;
        DrawText(labels[i], textX, by + i*80 + 15, 24, WHITE);
        
        if (i == selected_index) {
            MC_CircleFilled(SCREEN_W/2 - bw/2 + 25, by + i*80 + 27, 8, YELLOW);
        }
    }
}

void MenuView_DrawAbout(void) {
    DrawRectFill(0, 0, SCREEN_W, SCREEN_H, COL_SKY);
    
    const char *title = "TENTANG APLIKASI";
    int titleW = MeasureText(title, 40);
    DrawText(title, SCREEN_W/2 - titleW/2, 100, 40, WHITE);
    
    const char *desc = "Simulasi interaktif fenomena Gempa Bumi Tektonik.\n\n"
                       "Dibuat untuk tugas mata kuliah Grafika Komputer\n"
                       "menggunakan algoritma grafika manual (DDA, PolyFill, dll).\n\n"
                       "Oleh: 241524023\n\n"
                       "Tekan [BACKSPACE] untuk kembali.";
    DrawText(desc, 100, 220, 20, WHITE);
}
