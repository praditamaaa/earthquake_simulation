/* File: controller/menu_controller.c */
#include "menu_controller.h"
#include "app_controller.h"
#include <raylib.h>

void MenuController_HandleInput(struct AppController *ctrl) {
    if (ctrl->app_state.current_screen == SCREEN_ABOUT) {
        if (IsKeyPressed(KEY_BACKSPACE) || IsKeyPressed(KEY_ESCAPE) || IsKeyPressed(KEY_ENTER)) {
            AppState_SetScreen(&ctrl->app_state, SCREEN_MENU);
        }
        return;
    }

    if (ctrl->app_state.current_screen == SCREEN_MENU) {
        /* Only 3 buttons now */
        if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) {
            ctrl->menu_selected = (ctrl->menu_selected + 1) % 3;
        }
        if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) {
            ctrl->menu_selected = (ctrl->menu_selected - 1 + 3) % 3;
        }
        
        if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE)) {
            switch(ctrl->menu_selected) {
                case 0: /* Mulai Simulasi */
                    AppState_SetScreen(&ctrl->app_state, SCREEN_SIMULATION);
                    break;
                case 1: /* Tentang Aplikasi */
                    AppState_SetScreen(&ctrl->app_state, SCREEN_ABOUT);
                    break;
                case 2: /* Keluar */
                    ctrl->app_state.should_quit = 1;
                    break;
            }
        }
        
        /* Direct shortcuts */
        if (IsKeyPressed(KEY_ESCAPE)) {
            ctrl->app_state.should_quit = 1;
        }
    }
}
