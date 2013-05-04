
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
    bool go_on(void);
    void draw(void);
    bool frame_inc(void);
    void reset(void);
    inline void return_now(void)
    {
        this->returning = true;
    }
    private:
    int curr_frame;
    std::vector<ModelObject *> frames;
    bool use_starting;
    int frame_starting_nr;
    int frame_ending;
    bool returning;
};


#endif




