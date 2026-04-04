#include <raylib.h>
#include "app_state.h"
#include "app_controller.h"
#include "framebuffer.h"

int main(void) {
    InitWindow(SCREEN_W, SCREEN_H, "Simulasi Gempa Bumi - 241524023");
    SetTargetFPS(60);

    AppController ctrl;
    AppController_Init(&ctrl);

    while (!WindowShouldClose() && !ctrl.app_state.should_quit) {
        float dt = GetFrameTime();
        if (dt > 0.05f) dt = 0.05f;

        AppController_HandleInput(&ctrl);
        AppController_Update(&ctrl, dt);

        BeginDrawing();
        AppController_Draw(&ctrl);
        EndDrawing();
    }

    AppController_Destroy(&ctrl);
    CloseWindow();
    return 0;
}
