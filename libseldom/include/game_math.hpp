
#ifndef _GAME_MATH_H_
#define _GAME_MATH_H_

#include "global.hpp"

#include <vector>

/**
 * Well, in 3d space, a surface can write as:
 * 
 * ax+by+cz+d=0
 * 
 * With any three given points, this method can
 * calculate the a, b, c, d out. Someday we may
 * use them for working the z out with given x, 
 * y, etc.
 * 
 */
void get_face_abcd(double face[3][3], 
    double *a, double *b, double *c, double *d);
/**
 * See if point (x, y) in the given triangle.(2D Surface)
 */
bool in_2d_triangle(double x, double y, 
    double x1, double y1, double x2, double y2, double x3, double y3);
/**
 * Use Heron's formula to calculate give traingle's area.
 */
void get_triangle_s(
    double x1, double y1, double x2, double y2, double x3, double y3, 
    double *dest);
/**
 * Get the distance of the two given points.
 */
void get_distance(double x1, double y1, double x2, double y2, 
    double *dest);

#endif

