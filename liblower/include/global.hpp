
#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#define __DEBUG

// If building with VC++ on windows.
#ifdef _MSC_VER
#   include <windows.h>
#   define putenv _putenv
#endif

#ifndef PI
#   define PI 3.141592654
#endif

#include <string>

/**
 * Quit normally. Quit SDL first.
 * Can avoid making player's screen look 
 * funny after the game.
 */
void quit_game(void);
/**
 * Try to die properly. 
 * Out the error message as pretty as possible.
 * Quit with error code.
 */
void aborting(std::string errmsg);
/**
 * Abort with message tells unexpected.
 */
void aborting_unexpected(void);

extern int width, height;

// In windows it may not be the best. But, uh..
const std::string path_sep("/");
const std::string res_dir("res" + path_sep);

/**
 * Replace the "$" in given with "/" or other sep.
 */
std::string dollar_to_sep(std::string name);

#endif

