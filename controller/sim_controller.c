/* File: controller/sim_controller.c */
#include "sim_controller.h"
#include "app_controller.h"
#include "earthquake_model.h"
#include "raylib.h"

#include "framebuffer.h"

void SimController_HandleInput(struct AppController *ctrl) {
    AppState *s = &ctrl->app_state;
    EarthquakeModel *m = &s->earthquake_model;
    
    // Intensity Slider Mouse Interaction (bottom-center)
    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
        Vector2 mouse = GetMousePosition();
        int sx = SCREEN_W / 2 - 100;
        int sy = SCREEN_H - 80;
        if (mouse.x >= sx && mouse.x <= sx + 200 && mouse.y >= sy - 10 && mouse.y <= sy + 30) {
            float t = (mouse.x - (float)sx) / 200.0f;
            if (t < 0) t = 0;
            if (t > 1) t = 1;
            m->intensity = 0.5f + t * 2.0f; // Adjusted range to 0.5 - 2.5
        }
    }

    if (IsKeyPressed(KEY_ESCAPE) || IsKeyPressed(KEY_BACKSPACE)) {
        s->current_screen = SCREEN_MENU;
        EarthquakeModel_Reset(m);
    }
    
    if (IsKeyPressed(KEY_R)) {
        EarthquakeModel_Reset(m);
    }
    
    if (IsKeyPressed(KEY_P)) {
        m->paused = !m->paused;
    }
    
    // Cheat: Skip to tremor phase for testing
    if (IsKeyPressed(KEY_T)) {
        m->phase = EQ_PHASE_TREMOR;
        m->phase_timer = 0;
    }
}
