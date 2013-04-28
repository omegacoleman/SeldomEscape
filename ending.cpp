
#include "global.h"
#include <iostream>
#include <string>
#include <SDL/SDL.h>

void quit_scpark(void)
{
    SDL_Quit();
    exit(0);
}

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

void aborting_unexpected()
{
    aborting("Unexpected error. Aborted.");
}

