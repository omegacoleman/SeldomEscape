
#include "global.h"
#include "basegl.h"

#include <GL/gl.h>
#include <GL/glu.h>

static float ratio;

void setup_opengl(void)
{
    ratio = (float) width / (float) height;
    glShadeModel(GL_SMOOTH);
    // Counter clock wise will draw the front face.
    glFrontFace(GL_CCW);
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


