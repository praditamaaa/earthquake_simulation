/* File: controller/app_controller.h */
#ifndef APP_CONTROLLER_H
#define APP_CONTROLLER_H

#include "app_state.h"
#include "earthquake_model.h"

struct AppController {
    AppState app_state;
    int menu_selected;
};

typedef struct AppController AppController;

void AppController_Init(AppController *ctrl);
void AppController_Run(AppController *ctrl);
void AppController_HandleInput(AppController *ctrl);
void AppController_Update(AppController *ctrl, float dt);
void AppController_Draw(AppController *ctrl);
void AppController_Destroy(AppController *ctrl);

#endif
