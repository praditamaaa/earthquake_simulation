#ifndef PARTICLE_MODEL_H
#define PARTICLE_MODEL_H

#include <raylib.h>

/* File: model/particle_model.h */

#define MAX_PARTICLES 600

typedef enum {
    PARTICLE_LAVA = 0,
    PARTICLE_ROCK,
    PARTICLE_SMOKE,
    PARTICLE_DUST,
    PARTICLE_SPARK
} ParticleType;

typedef struct {
    float         x, y;
    float         vx, vy;
    float         ax, ay;         /* akselerasi (gravitasi, dll.) */
    float         life;
    float         max_life;
    float         radius;
    Color         color;
    ParticleType  type;
    int           active;
} Particle;

typedef struct {
    Particle pool[MAX_PARTICLES];
    int      count;
} ParticleSystem;

void ParticleSystem_Init(ParticleSystem *ps);
void ParticleSystem_Clear(ParticleSystem *ps);
void ParticleSystem_Spawn(ParticleSystem *ps,
                          float x, float y,
                          float vx, float vy,
                          float ax, float ay,
                          float life, float radius,
                          Color col, ParticleType type);
void ParticleSystem_SpawnBurst(ParticleSystem *ps,
                               float x, float y,
                               int count,
                               float min_speed, float max_speed,
                               float angle_min, float angle_max,
                               Color col, ParticleType type);
void ParticleSystem_Update(ParticleSystem *ps, float dt);

#endif /* PARTICLE_MODEL_H */