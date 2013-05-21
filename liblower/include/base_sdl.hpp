
#ifndef _BASE_SDL_HPP_
#define _BASE_SDL_HPP_

#include "global.hpp"
#include <SDL/SDL.h>

/**
 * Parse the given params and init OpenGL and SDL.
 */
void setup_sdl_for_gl(int argc, char* argv[]);
/**
 * Clear the event stack of SDL.
 * Will crash if not to do so.
 */
void process_events(void);

#endif


