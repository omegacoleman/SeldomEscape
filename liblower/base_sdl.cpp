
#include "global.hpp"
#include "base_sdl.hpp"

#include <string>

#include <SDL/SDL.h>

/**
 * Defined in main.cpp
 */
void handle_key_down(SDL_keysym* keysym);

/**
 * Parse the given params and init OpenGL and SDL.
 */
void setup_sdl_for_gl(int argc, char* argv[])
{
    // In order to place the window in the center of the screen..
    char a[] = "SDL_VIDEO_WINDOW_POS";
    char b[] = "SDL_VIDEO_CENTERED=1";
    putenv(a);
    putenv(b);
    
    // Normal settings.
    int flags = SDL_OPENGL | SDL_NOFRAME;
    int msaa_s_nr = 0;
    
    int i;
    for (i = 0; i < argc; i++)
    {
        std::string curr_param(argv[i]);
        // Ugly but safe..
        // Don't be scared..
        if (curr_param == "MSAA0")
        {
            msaa_s_nr = 0;
        }
        if (curr_param == "MSAA2")
        {
            msaa_s_nr = 2;
        }
        if (curr_param == "MSAA4")
        {
            msaa_s_nr = 4;
        }
        if (curr_param == "MSAA8")
        {
            msaa_s_nr = 8;
        }
        if (curr_param == "MSAA16")
        {
            msaa_s_nr = 16;
        }
        if (curr_param == "FS0")
        {
            flags &= ~SDL_FULLSCREEN;
        }
        if (curr_param == "FS1")
        {
            flags |= SDL_FULLSCREEN;
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
        if (curr_param == "SZ1024768")
        {
            width = 1024;
            height = 768;
        }
        if (curr_param == "SZ1360768")
        {
            width = 1360;
            height = 768;
        }
        if (curr_param == "SZ1366768")
        {
            width = 1366;
            height = 768;
        }
    }
    
    // Now init the SDL.
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        aborting((std::string)
            "Video initialization failed: " + SDL_GetError());
    }
    atexit(SDL_Quit); // Make sure to exit SDL when crashing.
    
    // Get the display's max bpp.
    const SDL_VideoInfo* info = SDL_GetVideoInfo();
    if(!info) {
        aborting((std::string)
            "Video query failed: " + SDL_GetError());
    }
    
    // Set attributes of SDL_GL environment.
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    if (msaa_s_nr) // MSAA may be troubled in Linux. 
    {
        SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
        SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, msaa_s_nr);
    }
    
    // Now get the video.
    if(SDL_SetVideoMode(width, height, 
        info->vfmt->BitsPerPixel, flags) == 0) {
        aborting((std::string)
            "Video mode set failed: " + SDL_GetError());
    }
}

/**
 * Clear the event stack of SDL.
 * Will crash if not to do so.
 */
void process_events(void)
{
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        switch(event.type) {
            case SDL_KEYDOWN:
            handle_key_down(&event.key.keysym);
            break;
            case SDL_QUIT:
            quit_game();
            break;
        }
    }
}

/**
 * Replace the "$" in given with "/" or other sep.
 */
std::string dollar_to_sep(std::string name)
{
    return std::string(name).replace(name.find("$"), 1, path_sep);
}

