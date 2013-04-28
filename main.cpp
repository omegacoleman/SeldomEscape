/*
 * SDL OpenGL Tutorial.
 * (c) Michael Vance, 2000
 * briareos@lokigames.com
 *
 * Distributed under terms of the LGPL. 
 */

#include "global.h"
#include "basegl.h"
#include "basesdl.h"
#include "image_loading.h"
#include "animloader.h"
#include "maps.h"
#include "math.h"

#include <string>
#include <exception>
#include <iostream>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>

#include "objload.h"

#ifndef PI
#   define PI 3.141592654
#endif

ModelObject *mm;
Land *l;

Anim *running_fleur;

GLuint texture;

static void draw_screen(void);

int width = 1024;
int height = 768;


double x = 0.0;
double y = 0.0;
double r = 0.0;

int main(int argc, char* argv[])
{
    std::set_unexpected(aborting_unexpected);
    setup_sdl_for_gl(argc, argv);
    setup_opengl();
    load_images();
    
    texture = get_texture("sea.jpg");
    mm = new ModelObject("maps$scpark", new MTLLibrary("maps$scpark"));
    l = new Land("maps$scpark");
    running_fleur = new Anim("fleur$running_000", 23, new MTLLibrary("fleur$def"));
    running_fleur->set_starting(7);
    
    while (1) {
        int tick_at_start = SDL_GetTicks();
        process_events();
        Uint8 *k = SDL_GetKeyState(NULL);
        if (k[SDLK_a])
        {
            x += sin((r-90)*PI/180.0) * 0.7;
            y -= cos((r-90)*PI/180.0) * 0.7;
        }
        if (k[SDLK_d])
        {
            x += sin((r+90)*PI/180.0) * 0.7;
            y -= cos((r+90)*PI/180.0) * 0.7;
        }
        if (k[SDLK_w])
        {
            x += sin(r*PI/180.0) * 0.7;
            y -= cos(r*PI/180.0) * 0.7;
        }
        if (k[SDLK_s])
        {
            x += sin((r+180)*PI/180.0) * 0.7;
            y -= cos((r+180)*PI/180.0) * 0.7;
        }
        if (k[SDLK_j])
        {
            r -= 3.7;
        }
        if (k[SDLK_l])
        {
            r += 3.7;
        }
        draw_screen();
        int tick_gone = SDL_GetTicks() - tick_at_start;
        if (40 > tick_gone)
        {
            SDL_Delay(40 - tick_gone);
        }
    }
    return 0;
}

static void draw_screen(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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

    start_gl_3d(true);
    glColor3d(1.0, 1.0, 1.0);
    glTranslated(0.0, -5.0, -5.0);
    glRotated(r, 0.0, 1.0, 0.0);
    glTranslated(-x, 0, -y);
    mm->obj_display();
    glTranslated(x, l->get_z_at(x, y), y);
    glRotated(r, 0.0, -1.0, 0.0);
    running_fleur->go_on();
    
    SDL_GL_SwapBuffers();
}


void handle_key_down(SDL_keysym* keysym)
{
    switch(keysym->sym) {
        case SDLK_ESCAPE:
        quit_scpark();
        break;
        default:
        break;
    }
}


