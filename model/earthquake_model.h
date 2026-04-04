/* File: model/earthquake_model.h */
#ifndef EARTHQUAKE_MODEL_H
#define EARTHQUAKE_MODEL_H

#include "matrix3x3.h"
#include "particle_model.h"

typedef enum {
  EQ_PHASE_IDLE = 0,
  EQ_PHASE_COLLISION,
  EQ_PHASE_SUBDUCTION,
  EQ_PHASE_TREMOR,
  EQ_PHASE_DONE,
  EQ_PHASE_COUNT
} EarthquakePhase;

typedef struct {
  EarthquakePhase phase;
  float phase_timer;
  float phase_duration[EQ_PHASE_COUNT];

  /* Plate Movement */
  float right_plate_offset_x;
  float left_plate_offset_x;
  float subduction_angle;
  float subduction_depth;
  float left_plate_uplift_y;

  /* Earthquake Shake */
  float shake_intensity;
  float shake_x_offset;
  float shake_y_offset;

  /* Buildings */
  float building_shake[12];
  int building_damaged[12];
  float building_fragility[12]; // Variation in resistance (0.5 to 1.5)

  float cloud_timer;
  float intensity; // 0.5 to 2.5
  int paused;
} EarthquakeModel;

void EarthquakeModel_Init(EarthquakeModel *m);
void EarthquakeModel_Update(EarthquakeModel *m, float dt);
void EarthquakeModel_Reset(EarthquakeModel *m);
float EarthquakeModel_GetPhaseProgress(const EarthquakeModel *m);

#endif