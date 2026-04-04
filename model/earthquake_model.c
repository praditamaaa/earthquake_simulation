/* File: model/earthquake_model.c */
#include "earthquake_model.h"
#include "math_utils.h"
#include <math.h>
#include <stdlib.h>

void EarthquakeModel_Init(EarthquakeModel *m) {
  m->phase_duration[EQ_PHASE_IDLE] = 2.0f;
  m->phase_duration[EQ_PHASE_COLLISION] = 3.0f;
  m->phase_duration[EQ_PHASE_SUBDUCTION] = 4.0f;
  m->phase_duration[EQ_PHASE_TREMOR] = 7.0f; // Longer tremor
  m->phase_duration[EQ_PHASE_DONE] = 2.0f;

  EarthquakeModel_Reset(m);
}

void EarthquakeModel_Reset(EarthquakeModel *m) {
  m->phase = EQ_PHASE_IDLE;
  m->phase_timer = 0.0f;

  m->right_plate_offset_x = 0.0f;
  m->left_plate_offset_x = 0.0f;
  m->subduction_angle = 0.0f;
  m->subduction_depth = 0.0f;
  m->left_plate_uplift_y = 0.0f;

  m->shake_intensity = 0.0f;
  m->shake_x_offset = 0.0f;
  m->shake_y_offset = 0.0f;

  for (int i = 0; i < 12; i++) {
    m->building_shake[i] = 0.0f;
    m->building_damaged[i] = 0;
    m->building_fragility[i] = 0.5f + ((float)rand() / RAND_MAX); // 0.5 to 1.5
  }
  m->intensity = 1.0f;
  m->cloud_timer = 0.0f;
  m->paused = 0;
}

float EarthquakeModel_GetPhaseProgress(const EarthquakeModel *m) {
  if (m->phase >= EQ_PHASE_COUNT)
    return 1.0f;
  if (m->phase_duration[m->phase] <= 0.0f)
    return 1.0f;
  return m->phase_timer / m->phase_duration[m->phase];
}

void EarthquakeModel_Update(EarthquakeModel *m, float dt) {
  if (m->paused)
    return;

  m->phase_timer += dt;
  m->cloud_timer += dt * 30.0f; // Constant cloud movement speed

  if (m->phase_timer >= m->phase_duration[m->phase] &&
      m->phase < EQ_PHASE_DONE) {
    m->phase_timer = 0.0f;
    m->phase++;
    while (m->phase < EQ_PHASE_DONE && m->phase_duration[m->phase] <= 0.0f) {
      m->phase++;
    }
  }



  if (m->shake_intensity > 0.0f) {
    float scaled_shake = m->shake_intensity * m->intensity;
    m->shake_x_offset = sinf(m->phase_timer * 40.0f) * scaled_shake;
    m->shake_y_offset =
        cosf(m->phase_timer * 30.0f) * scaled_shake * 0.4f;
  }

  switch (m->phase) {
  case EQ_PHASE_COLLISION:
    m->shake_intensity = 1.0f;
    break;
  case EQ_PHASE_SUBDUCTION:
    // Only shake, no movement
    m->shake_intensity = 3.0f;
    break;
  case EQ_PHASE_TREMOR:
    // Balanced shake intensity (max ~12.5px @ 2.5x intensity)
    m->shake_intensity = 5.0f * m->intensity;

    for (int i = 0; i < 12; i++) {
        if (m->building_damaged[i] < 4) {
            float roll = (float)rand() / (float)RAND_MAX;
            // Scale damage probability by building fragility
            float prob_scale = m->intensity * (m->shake_intensity / 5.0f) * m->building_fragility[i];
            if (roll < 0.04f * prob_scale)
                m->building_damaged[i]++; 
        }
    }
    break;
  case EQ_PHASE_DONE:
    m->shake_intensity = 0.0f;
    break;
  default:
    break;
  }
}