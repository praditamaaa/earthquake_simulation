#ifndef HUD_VIEW_H
#define HUD_VIEW_H

#include <raylib.h>

/* File: view/hud_view.h */

void HudView_DrawInfo(const char *scenario_name,
                      const char *phase_name,
                      float phase_progress,
                      int paused,
                      int show_debug);

void HudView_DrawIntensitySlider(float intensity);

#endif /* HUD_VIEW_H */
