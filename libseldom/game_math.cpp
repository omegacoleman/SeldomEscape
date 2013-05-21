
#include "game_math.hpp"
#include <cmath>
#include <iostream>

/**
 * I don't wanna see this code any more..
 * 
 * Well, in 3d space, a surface can write as:
 * 
 * ax+by+cz+d=0
 * 
 * With any three given points, this method can
 * calculate the a, b, c, d out. Someday we may
 * use them for working the z out with given x, 
 * y, etc.
 * 
 * The code is very ugly, but .. Uh, just bring
 * your goggles.
 * 
 */
void get_face_abcd(double face[3][3], 
double *a, double *b, double *c, double *d)
{
    *a = (face[1][1]-face[0][1])*(face[2][2]-face[0][2])-(face[1][2]-face[0][2])*(face[2][1]-face[0][1]);
    *b = (face[1][2]-face[0][2])*(face[2][0]-face[0][0])-(face[1][0]-face[0][0])*(face[2][2]-face[0][2]);
    *c = (face[1][0]-face[0][0])*(face[2][1]-face[0][1])-(face[1][1]-face[0][1])*(face[2][0]-face[0][0]);
    *d = -(*a)*face[0][0]-(*b)*face[0][1]-(*c)*face[0][2];
}

/**
 * See if point (x, y) in the given triangle.(2D Surface)
 * 
 */
bool in_2d_triangle(double x, double y, 
    double x1, double y1, double x2, double y2, double x3, double y3)
{
    double s, s_a, s_b, s_c;
    // Calculate the three separated traingles' area.
    get_triangle_s(x1, y1, x2, y2, x3, y3, &s);
    get_triangle_s(x1, y1, x2, y2, x, y, &s_a);
    get_triangle_s(x2, y2, x3, y3, x, y, &s_b);
    // Calculate the given traingle's area.
    get_triangle_s(x1, y1, x3, y3, x, y, &s_c);
    // If similiar, then this is it!
    return (((s_a + s_b + s_c) - s) <= 0.001);
}

/**
 * Use Heron's formula to calculate give traingle's area.
 */
void get_triangle_s(
    double x1, double y1, double x2, double y2, double x3, double y3, 
    double *dest)
{
    double a, b, c, p;
    get_distance(x1, y1, x2, y2, &a);
    get_distance(x2, y2, x3, y3, &b);
    get_distance(x3, y3, x1, y1, &c);
    // Nothing special. Just the formula itself.
    // See : 
    // http://mathworld.wolfram.com/HeronsFormula.html (English)
    // http://zh.wikipedia.org/zh/%E6%B5%B7%E4%BC%A6%E5%85%AC%E5%BC%8F
    // (Chinese)
    p = (a + b + c) / 2;
    *dest = sqrt(p * (p - a) * (p - b) * (p - c));
}

/**
void calc_line(double x1, double y1, double x2, double y2, 
    double *dest_k, double *dest_b)
{
    if (x1 == x2)
    {
        *dest_k = 100000.0;
        *dest_b = y1;
        return;
    }
    *dest_k = (y1 - y2) / (x1 - x2);
    *dest_b = y1 - (x1 * (*dest_k));
}

void get_public(double k1, double b1, double k2, double b2, 
    double *dest_x, double *dest_y)
{
    *dest_x = (b2 - b1) / (k1 - k2);
    *dest_y = b1 + (k1 * (*dest_x));
}

void get_middle(double x1, double y1, double x2, double y2, 
    double *dest_x, double *dest_y)
{
    *dest_x = (x1 + x2) / 2;
    *dest_y = (y1 + y2) / 2;
}
**/

/**
 * Get the distance of the two given points.
 */
void get_distance(double x1, double y1, double x2, double y2, 
    double *dest)
{
    *dest = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}


