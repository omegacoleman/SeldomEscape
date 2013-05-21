
#ifndef _BASE_GL_HPP_
#define _BASE_GL_HPP_

#include "global.hpp"

#include <GL/gl.h>

/**
 * Set some param inside GL.
 * Including:
 *      Shade smoothly;
 *      Draw the front face in CCW;
 *      MSAA enabled.
 */
void setup_opengl(void);
/**
 * Call before drawing 2d or 3d faces.
 */
void start_gl_3d(const bool three_d);
/**
 * Fill the screen with the texture given.
 */
void draw_fullscreen(GLuint texture);

/**
 * Call before drawing every frame, in order to make sure 
 * buffers cleaned.
 */
void start_drawing(void);

#endif

