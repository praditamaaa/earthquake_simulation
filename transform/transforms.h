#ifndef TRANSFORMS_H
#define TRANSFORMS_H

#include "matrix3x3.h"

/* File: transform/transforms.h */

void Trans_Translate(float tx, float ty, Mat3 *out);
void Trans_Scale(float sx, float sy, Mat3 *out);
void Trans_ScaleAround(float sx, float sy, float cx, float cy, Mat3 *out);
void Trans_Rotate(float angle_rad, Mat3 *out);
void Trans_RotateAround(float angle_rad, float cx, float cy, Mat3 *out);
void Trans_ReflectX(Mat3 *out);
void Trans_ReflectY(Mat3 *out);
void Trans_ReflectLine(float angle_rad, Mat3 *out);
void Trans_ShearX(float kx, Mat3 *out);
void Trans_ShearY(float ky, Mat3 *out);

void Trans_Compose(const Mat3 *transforms, int n, Mat3 *out);

#endif /* TRANSFORMS_H */
