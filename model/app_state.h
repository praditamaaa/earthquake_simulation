#ifndef APP_STATE_H
#define APP_STATE_H

#include "earthquake_model.h"

/* File: model/app_state.h */

typedef enum {
    SCREEN_MENU = 0,
    SCREEN_SIMULATION,
    SCREEN_OBJECT,
    SCREEN_ABOUT
} ScreenType;

typedef struct {
    ScreenType current_screen;
    ScreenType previous_screen;
    float      total_time;
    int        should_quit;
    
    /* Simulation Models */
    EarthquakeModel earthquake_model;
} AppState;

void AppState_Init(AppState *s);
void AppState_Update(AppState *s, float dt);
void AppState_SetScreen(AppState *s, ScreenType screen);

#endif /* APP_STATE_H */