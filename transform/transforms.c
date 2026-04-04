/* File: transform/transforms.c */
#include "transforms.h"
#include <math.h>

void Trans_Translate(float tx, float ty, Mat3 *out) {
    *out = Mat3_Identity();
    out->m[0][2] = tx;
    out->m[1][2] = ty;
}

void Trans_Scale(float sx, float sy, Mat3 *out) {
    *out = Mat3_Identity();
    out->m[0][0] = sx;
    out->m[1][1] = sy;
}

void Trans_ScaleAround(float sx, float sy, float cx, float cy, Mat3 *out) {
    Mat3 m1, m2, m3;
    Trans_Translate(-cx, -cy, &m1);
    Trans_Scale(sx, sy, &m2);
    Trans_Translate(cx, cy, &m3);
    Mat3 mats[3] = {m1, m2, m3};
    Trans_Compose(mats, 3, out);
}

void Trans_Rotate(float angle_rad, Mat3 *out) {
    *out = Mat3_Identity();
    float c = cosf(angle_rad);
    float s = sinf(angle_rad);
    out->m[0][0] = c;  out->m[0][1] = -s;
    out->m[1][0] = s;  out->m[1][1] = c;
}

void Trans_RotateAround(float angle_rad, float cx, float cy, Mat3 *out) {
    Mat3 m1, m2, m3;
    Trans_Translate(-cx, -cy, &m1);
    Trans_Rotate(angle_rad, &m2);
    Trans_Translate(cx, cy, &m3);
    Mat3 mats[3] = {m1, m2, m3};
    Trans_Compose(mats, 3, out);
}

void Trans_ReflectX(Mat3 *out) {
    *out = Mat3_Identity();
    out->m[1][1] = -1.0f;
}

void Trans_ReflectY(Mat3 *out) {
    *out = Mat3_Identity();
    out->m[0][0] = -1.0f;
}

void Trans_ReflectLine(float angle_rad, Mat3 *out) {
    Mat3 m1, m2, m3;
    Trans_Rotate(-angle_rad, &m1);
    Trans_ReflectX(&m2);
    Trans_Rotate(angle_rad, &m3);
    Mat3 mats[3] = {m1, m2, m3};
    Trans_Compose(mats, 3, out);
}

void Trans_ShearX(float kx, Mat3 *out) {
    *out = Mat3_Identity();
    out->m[0][1] = kx;
}

void Trans_ShearY(float ky, Mat3 *out) {
    *out = Mat3_Identity();
    out->m[1][0] = ky;
}

void Trans_Compose(const Mat3 *transforms, int n, Mat3 *out) {
    if (n <= 0) {
        *out = Mat3_Identity();
        return;
    }
    *out = transforms[0];
    for (int i = 1; i < n; i++) {
        *out = Mat3_Multiply(transforms[i], *out);
    }
}
