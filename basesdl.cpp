
#include "global.h"
#include "basesdl.h"

#include <string>
#include <iostream>

#include <SDL/SDL.h>

void handle_key_down(SDL_keysym* keysym);

void setup_sdl_for_gl(int argc, char* argv[])
{
    int flags = SDL_OPENGL | SDL_FULLSCREEN;
    int msaa_s_nr = 4;
    int i;
    for (i = 0; i < argc; i++)
    {
        std::string curr_param(argv[i]);
        if (curr_param == "MSAA2")
        {
            msaa_s_nr = 2;
        }
        if (curr_param == "MSAA8")
        {
            msaa_s_nr = 8;
        }
        if (curr_param == "MSAA16")
        {
            msaa_s_nr = 16;
        }
        if (curr_param == "MSAA0")
        {
            msaa_s_nr = 0;
        }
        if (curr_param == "FS0")
        {
            flags -= SDL_FULLSCREEN;
        }
        if (curr_param == "SZ800600")
        {
            width = 800;
            height = 600;
        }
        if (curr_param == "SZ600400")
        {
            width = 600;
            height = 400;
        }
        if (curr_param == "SZ1366768")
        {
            width = 1366;
            height = 768;
        }
        if (curr_param == "SZ1360768")
        {
            width = 1360;
            height = 768;
        }
        if (curr_param == "SZ1024768")
        {
            width = 1024;
            height = 768;
        }
    }
    const SDL_VideoInfo* info = NULL;
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        aborting((std::string)
            "Video initialization failed: " + SDL_GetError());
    }
    atexit(SDL_Quit);
    info = SDL_GetVideoInfo();
    if(!info) {
        aborting((std::string)
            "Video query failed: " + SDL_GetError());
    }
    const int bpp = info->vfmt->BitsPerPixel;
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    if (msaa_s_nr)
    {
        SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
        SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, msaa_s_nr);
    }
    if(SDL_SetVideoMode(width, height, bpp, flags) == 0) {
        aborting((std::string)
            "Video mode set failed: " + SDL_GetError());
    }
}

void process_events(void)
{
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        switch(event.type) {
            case SDL_KEYDOWN:
            handle_key_down(&event.key.keysym);
            break;
            case SDL_QUIT:
            quit_scpark();
            break;
        }
    }
}


std::string dollar_to_sep(std::string name)
{
    return std::string(name).replace(name.find("$"), 1, path_sep);
}

