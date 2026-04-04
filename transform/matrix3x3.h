#ifndef MATRIX3X3_H
#define MATRIX3X3_H

/* File: transform/matrix3x3.h */

typedef struct {
    float m[3][3];
} Mat3;

typedef struct {
    float x;
    float y;
} Vec2;

Mat3  Mat3_Identity(void);
Mat3  Mat3_Multiply(Mat3 a, Mat3 b);
void  Mat3_ApplyPoint(Mat3 m, float x, float y, float *out_x, float *out_y);
void  Mat3_ApplyPolygon(Mat3 m, const Vec2 *in_verts, Vec2 *out_verts, int n);

#endif /* MATRIX3X3_H */
