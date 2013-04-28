
#ifndef _GAME_MATH_H_
#define _GAME_MATH_H_

#include <vector>

void get_face_abcd(double face[3][3], 
    double *a, double *b, double *c, double *d);
bool in_2d_triangle(double x, double y, 
    double x1, double y1, double x2, double y2, double x3, double y3);
void calc_line(double x1, double y1, double x2, double y2, 
    double *dest_k, double *dest_b);
void get_public(double k1, double b1, double k2, double b2, 
    double *dest_x, double *dest_y);
void get_middle(double x1, double y1, double x2, double y2, 
    double *dest_x, double *dest_y);
void get_distance(double x1, double y1, double x2, double y2, 
    double *dest);
void get_triangle_s(
    double x1, double y1, double x2, double y2, double x3, double y3, 
    double *dest);

#endif

