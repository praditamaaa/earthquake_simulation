/* File: controller/app_controller.c */
#include "app_controller.h"
#include "menu_view.h"
#include "earthquake_view.h"
#include "menu_controller.h"
#include "sim_controller.h"
#include "raylib.h"

void AppController_Init(AppController *ctrl) {
    AppState_Init(&ctrl->app_state);
    ctrl->menu_selected = 0;
}

void AppController_HandleInput(AppController *ctrl) {
    if (ctrl->app_state.current_screen == SCREEN_MENU || ctrl->app_state.current_screen == SCREEN_ABOUT || ctrl->app_state.current_screen == SCREEN_OBJECT) {
        MenuController_HandleInput(ctrl);
    } else if (ctrl->app_state.current_screen == SCREEN_SIMULATION) {
        SimController_HandleInput(ctrl);
    }
}

void AppController_Update(AppController *ctrl, float dt) {
    if (ctrl->app_state.current_screen == SCREEN_SIMULATION) {
        EarthquakeModel_Update(&ctrl->app_state.earthquake_model, dt);
    }
    AppState_Update(&ctrl->app_state, dt);
}

void AppController_Draw(AppController *ctrl) {
    switch (ctrl->app_state.current_screen) {
        case SCREEN_MENU:
            MenuView_DrawMain(ctrl->menu_selected);
            break;
        case SCREEN_ABOUT:
            MenuView_DrawAbout();
            break;
        case SCREEN_SIMULATION:
            EarthquakeView_Draw(&ctrl->app_state);
            break;
        case SCREEN_OBJECT:
            MenuView_DrawObject();
            break;
        default:
            break;
    }
}

void AppController_Run(AppController *ctrl) {
    while (!WindowShouldClose() && !ctrl->app_state.should_quit) {
        float dt = GetFrameTime();
        AppController_HandleInput(ctrl);
        AppController_Update(ctrl, dt);
        
        BeginDrawing();
        AppController_Draw(ctrl);
        EndDrawing();
    }
}


void AppController_Destroy(AppController *ctrl) {

    
}