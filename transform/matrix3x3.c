/* File: transform/matrix3x3.c */
#include "matrix3x3.h"
#include <string.h>

Mat3 Mat3_Identity(void) {
    Mat3 out;
    memset(&out, 0, sizeof(Mat3));
    out.m[0][0] = 1.0f;
    out.m[1][1] = 1.0f;
    out.m[2][2] = 1.0f;
    return out;
}

Mat3 Mat3_Multiply(Mat3 a, Mat3 b) {
    Mat3 out;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            out.m[i][j] = a.m[i][0] * b.m[0][j] + 
                          a.m[i][1] * b.m[1][j] + 
                          a.m[i][2] * b.m[2][j];
        }
    }
    return out;
}

void Mat3_ApplyPoint(Mat3 m, float x, float y, float *out_x, float *out_y) {
    float nx = x * m.m[0][0] + y * m.m[0][1] + 1.0f * m.m[0][2];
    float ny = x * m.m[1][0] + y * m.m[1][1] + 1.0f * m.m[1][2];
    float nw = x * m.m[2][0] + y * m.m[2][1] + 1.0f * m.m[2][2];
    
    if (nw != 0.0f && nw != 1.0f) {
        nx /= nw;
        ny /= nw;
    }
    *out_x = nx;
    *out_y = ny;
}

void Mat3_ApplyPolygon(Mat3 m, const Vec2 *in_verts, Vec2 *out_verts, int n) {
    for (int i = 0; i < n; i++) {
        Mat3_ApplyPoint(m, in_verts[i].x, in_verts[i].y, &out_verts[i].x, &out_verts[i].y);
    }
}
