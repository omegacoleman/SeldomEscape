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
#include "creature.h"

#include <string>
#include <exception>
#include <iostream>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>

#include "objload.h"


GameMap *m;

Creature *fleur;

GLuint texture;

static void draw_screen(void);

int width = 1024;
int height = 768;

double r = 0.0;

int main(int argc, char* argv[])
{
    std::set_unexpected(aborting_unexpected);
    setup_sdl_for_gl(argc, argv);
    setup_opengl();
    load_images();
    
    texture = get_texture("sea.jpg");
    m = new GameMap("maps$scpark");
    m->add_item("maps$toilet", 12.0, 0.0);
    fleur = new Creature("Fleur Coleman", "fleur", m);
    fleur->add_action(ext_a_running, 23, 7);
    // fleur->set_starting(7);
    
    while (1) {
        int tick_at_start = SDL_GetTicks();
        process_events();
        Uint8 *k = SDL_GetKeyState(NULL);
        double m_r = r;
        if (k[SDLK_a])
        {
            m_r -= 90.0;
        }
        if (k[SDLK_d])
        {
            m_r += 90.0;
        }
        if (k[SDLK_w])
        {
        }
        if (k[SDLK_s])
        {
            m_r += 180.0;
        }
        if (k[SDLK_w] or k[SDLK_a] or k[SDLK_s] or k[SDLK_d])
        {
            fleur->move_rotated(m_r, 0.7);
            fleur->do_action(ext_a_running);
        } else {
            fleur->do_action("");
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
    glTranslated(0.0, -3.0, -10.0);
    glRotated(15.0, 1.0, 0.0, 0.0);
    glRotated(r, 0.0, 1.0, 0.0);
    fleur->camera_this();
    m->draw();
    fleur->draw();
    
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


