#ifndef MATH_UTILS_H
#define MATH_UTILS_H

/* File: core/math_utils.h */

#define PI        3.14159265358979323846f
#define TWO_PI    6.28318530717958647692f
#ifndef DEG2RAD
#define DEG2RAD   (PI / 180.0f)
#endif
#ifndef RAD2DEG
#define RAD2DEG   (180.0f / PI)
#endif

float Math_Lerp(float a, float b, float t);
float Math_Clamp(float v, float lo, float hi);
float Math_Smoothstep(float t);   /* 3t^2 - 2t^3 */
float Math_EaseIn(float t);       /* t^2 */
float Math_EaseOut(float t);      /* 1 - (1-t)^2 */
float Math_EaseInOut(float t);    /* sinf-based */
int   Math_Sign(float v);         /* -1, 0, atau 1 */
float Math_Abs(float v);

#endif /* MATH_UTILS_H */
