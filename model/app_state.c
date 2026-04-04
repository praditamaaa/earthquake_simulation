/* File: model/app_state.c */
#include "app_state.h"
#include "earthquake_model.h"

void AppState_Init(AppState *s) {
    s->current_screen = SCREEN_MENU;
    s->previous_screen = SCREEN_MENU;
    s->total_time = 0.0f;
    s->should_quit = 0;
    
    EarthquakeModel_Init(&s->earthquake_model);
}

void AppState_Update(AppState *s, float dt) {
    s->total_time += dt;
}

void AppState_SetScreen(AppState *s, ScreenType screen) {
    s->previous_screen = s->current_screen;
    s->current_screen = screen;
}
