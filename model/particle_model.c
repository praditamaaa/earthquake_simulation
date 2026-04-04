/* File: model/particle_model.c */
#include "particle_model.h"
#include "math_utils.h"
#include <stdlib.h>
#include <math.h>

void ParticleSystem_Init(ParticleSystem *ps) {
    ParticleSystem_Clear(ps);
}

void ParticleSystem_Clear(ParticleSystem *ps) {
    ps->count = 0;
    for (int i = 0; i < MAX_PARTICLES; i++) {
        ps->pool[i].active = 0;
    }
}

void ParticleSystem_Spawn(ParticleSystem *ps,
                          float x, float y,
                          float vx, float vy,
                          float ax, float ay,
                          float life, float radius,
                          Color col, ParticleType type) {
    if (ps->count >= MAX_PARTICLES) return;
    
    for (int i = 0; i < MAX_PARTICLES; i++) {
        if (!ps->pool[i].active) {
            ps->pool[i].x = x;
            ps->pool[i].y = y;
            ps->pool[i].vx = vx;
            ps->pool[i].vy = vy;
            ps->pool[i].ax = ax;
            ps->pool[i].ay = ay;
            ps->pool[i].life = life;
            ps->pool[i].max_life = life;
            ps->pool[i].radius = radius;
            ps->pool[i].color = col;
            ps->pool[i].type = type;
            ps->pool[i].active = 1;
            ps->count++;
            return;
        }
    }
}

void ParticleSystem_SpawnBurst(ParticleSystem *ps,
                               float x, float y,
                               int count,
                               float min_speed, float max_speed,
                               float angle_min, float angle_max,
                               Color col, ParticleType type) {
    for (int i = 0; i < count; i++) {
        if (ps->count >= MAX_PARTICLES) break;
        
        float spd = min_speed + (float)rand() / (float)RAND_MAX * (max_speed - min_speed);
        float a = angle_min + (float)rand() / (float)RAND_MAX * (angle_max - angle_min);
        float ax = 0.0f;
        float ay = 0.0f;
        float life = 1.0f + (float)rand() / (float)RAND_MAX * 1.5f;
        float radius = 2.0f + (float)rand() / (float)RAND_MAX * 4.0f;
        
        if (type == PARTICLE_DUST) {
            ay = -10.0f; /* mengambang ke atas */
        } else if (type == PARTICLE_ROCK) {
            ay = 500.0f; /* gravitasi kuat */
        } else if (type == PARTICLE_LAVA) {
            ay = 300.0f;
        } else if (type == PARTICLE_SMOKE) {
            ay = -20.0f;
        }
        
        float vx = cosf(a * DEG2RAD) * spd;
        float vy = sinf(a * DEG2RAD) * spd;
        
        ParticleSystem_Spawn(ps, x, y, vx, vy, ax, ay, life, radius, col, type);
    }
}

void ParticleSystem_Update(ParticleSystem *ps, float dt) {
    for (int i = 0; i < MAX_PARTICLES; i++) {
        if (ps->pool[i].active) {
            ps->pool[i].life -= dt;
            if (ps->pool[i].life <= 0.0f) {
                ps->pool[i].active = 0;
                ps->count--;
            } else {
                ps->pool[i].vx += ps->pool[i].ax * dt;
                ps->pool[i].vy += ps->pool[i].ay * dt;
                ps->pool[i].x += ps->pool[i].vx * dt;
                ps->pool[i].y += ps->pool[i].vy * dt;
            }
        }
    }
}
