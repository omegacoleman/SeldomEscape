
#include "global.hpp"
#include "base_gl.hpp"

#include <GL/gl.h>
#include <GL/glu.h>

static float ratio;

/**
 * Set some param inside GL.
 * Including:
 *      Shade smoothly;
 *      Draw the front face in CCW;
 *      MSAA enabled.
 */
void setup_opengl(void)
{
    ratio = (float) width / (float) height;
    
    // Smooth shade looks better.
    glShadeModel(GL_SMOOTH);
    
    glViewport(0, 0, width, height);
    
    // Enable MSAA.
    glEnable(GL_POLYGON_SMOOTH);
    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
}

/**
 * Call before drawing 2d or 3d faces.
 */
void start_gl_3d(const bool three_d)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (three_d) {
        gluPerspective(60.0f, ratio, 1.0f, 1024.0f);
    } else {
        gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
    }
    glMatrixMode(GL_MODELVIEW);  
    glLoadIdentity();
    if (three_d) {
        glEnable(GL_DEPTH_TEST);
    } else {
        glDisable(GL_DEPTH_TEST);
    }
}

/**
 * Fill the screen with the texture given.
 */
void draw_fullscreen(GLuint texture)
{
    start_gl_3d(false);
    glColor3d(1.0, 1.0, 1.0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glEnable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
        glTexCoord2d(0.0, 1.0);glVertex2d(-1.0, 1.0);
        glTexCoord2d(0.0, 0.0);glVertex2d(-1.0,-1.0);
        glTexCoord2d(1.0, 0.0);glVertex2d( 1.0,-1.0);
        glTexCoord2d(1.0, 1.0);glVertex2d( 1.0, 1.0);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

/**
 * Call before drawing every frame, in order to make sure 
 * buffers cleaned.
 */
void start_drawing(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


