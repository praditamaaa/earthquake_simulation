/* File: core/math_utils.c */
#include "math_utils.h"
#include <math.h>

float Math_Lerp(float a, float b, float t) {
    return a + (b - a) * t;
}

float Math_Clamp(float v, float lo, float hi) {
    if (v < lo) return lo;
    if (v > hi) return hi;
    return v;
}

float Math_Smoothstep(float t) {
    if (t < 0.0f) return 0.0f;
    if (t > 1.0f) return 1.0f;
    return t * t * (3.0f - 2.0f * t);
}

float Math_EaseIn(float t) {
    if (t < 0.0f) return 0.0f;
    if (t > 1.0f) return 1.0f;
    return t * t;
}

float Math_EaseOut(float t) {
    if (t < 0.0f) return 0.0f;
    if (t > 1.0f) return 1.0f;
    return 1.0f - (1.0f - t) * (1.0f - t);
}

float Math_EaseInOut(float t) {
    if (t < 0.0f) return 0.0f;
    if (t > 1.0f) return 1.0f;
    return 0.5f * (1.0f - cosf(PI * t));
}

int Math_Sign(float v) {
    if (v < 0.0f) return -1;
    if (v > 0.0f) return 1;
    return 0;
}

float Math_Abs(float v) {
    return (v < 0.0f) ? -v : v;
}
