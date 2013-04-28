
#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#ifdef _MSC_VER
#   include <windows.h>
#endif

#include <string>

void quit_scpark(void);
void aborting(std::string errmsg);
void aborting_unexpected(void);

extern int width, height;

const std::string path_sep("/");

const std::string res_dir("res" + path_sep);

std::string dollar_to_sep(std::string name);

#endif

