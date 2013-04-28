
#ifndef _ANIM_LOADER_H_
#define _ANIM_LOADER_H_

#include <string>
#include <vector>

#include "objload.h"

class Anim
{
    public:
    Anim(std::string basename, int frames_nr, MTLLibrary *mtllib);
    void set_starting(int starting);
    void go_on(void);
    void draw(void);
    void frame_inc(void);
    private:
    int curr_frame;
    std::vector<ModelObject *> frames;
    bool use_starting;
    int frame_starting_nr;
    int frame_ending;
};


#endif




