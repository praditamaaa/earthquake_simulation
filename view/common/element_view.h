#ifndef ELEMENT_VIEW_H
#define ELEMENT_VIEW_H

#include <raylib.h>
#include "matrix3x3.h"

/* File: view/common/element_view.h */

/**
 * Draw a bold sun with thick triangular rays.
 * @param cx Center X
 * @param cy Center Y
 * @param r Radius of core
 */
void Draw_BoldSun(int cx, int cy, int r);

/**
 * Draw a fluffy cloud using multiple overlapping circles.
 * @param x Anchor X (left)
 * @param y Anchor Y (bottom)
 * @param width Target horizontal span
 */
void Draw_FluffyCloud(int x, int y, int width);

/**
 * Draw a detailed building with windows and damage states.
 * @param transform Mat3 transform for positioning and tilt
 * @param w Width of building
 * @param h Height of building
 * @param wall Color of the walls
 * @param roof Color of the roof
 * @param state 0: Normal, 1: Cracked, 2: Collapsed
 */
void Draw_DetailedBuilding(Mat3 transform, float w, float h, Color wall, Color roof, int state);

/**
 * Draw a simple residential house with a triangular roof.
 * @param transform Mat3 transform for positioning
 * @param w Width of building
 * @param h Height of building
 * @param wall Color of the walls
 * @param roof Color of the roof
 * @param state 0: Normal, 1: Cracked, 2: Collapsed
 */
void Draw_SimpleHouse(Mat3 transform, float w, float h, Color wall, Color roof, int state);

/**
 * Draw a simple residential house with a triangular roof.
 * @param transform Mat3 transform for positioning
 * @param w Width of building
 * @param h Height of building
 * @param wall Color of the walls
 * @param roof Color of the roof
 * @param state 0: Normal, 1: Cracked, 2: Collapsed
 */
void Draw_Building2(Mat3 transform, float w, float h, Color wall, Color roof, int state);


#endif /* ELEMENT_VIEW_H */
