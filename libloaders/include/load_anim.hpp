
#ifndef _ANIM_LOADER_HPP_
#define _ANIM_LOADER_HPP_

#include "global.hpp"
#include "load_obj.hpp"

#include <string>
#include <vector>


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




