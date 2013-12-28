

#ifndef _TXTLOAD_HPP_
#define _TXTLOAD_HPP_

#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>

void init_text(std::string charmap_filename);
void draw_char(char c, double x, double y, double size);
void draw_str(char* s, unsigned int len, double x, double y, double size);
void draw_string(std::string s, double x, double y, double size);

#endif
