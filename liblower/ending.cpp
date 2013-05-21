
#include "global.hpp"

#include <iostream>
#include <string>
#include <SDL/SDL.h>

/**
 * Quit normally. Quit SDL first.
 * Can avoid making player's screen look 
 * funny after the game.
 */
void quit_game(void)
{
    SDL_Quit();
    exit(0);
}

/**
 * Try to die properly. 
 * Out the error message as pretty as possible.
 * Quit with error code.
 */
void aborting(std::string errmsg)
{
    #ifdef _MSC_VER
        MessageBox(NULL, errmsg.c_str(), "Aborted", MB_OK);
    #else
        std::cerr << errmsg << std::endl;
    #endif
    SDL_Quit();
    exit(1);
}

/**
 * Abort with message tells unexpected.
 */
void aborting_unexpected()
{
    aborting("Unexpected error. Aborted.");
}

