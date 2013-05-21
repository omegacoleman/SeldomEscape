
#include "global.hpp"
#include "load_anim.hpp"
#include "load_obj.hpp"

#include <string>
#include <sstream>
#include <iomanip>

Anim::Anim(std::string basename, int frames_nr, MTLLibrary *mtllib)
:frame_ending(frames_nr), 
    frames(), curr_frame(0), use_starting(false), returning(false)
{
    int i;
    for (i = 1; i <= frames_nr; i++)
    {
        std::string curr_filename(basename);
        std::ostringstream curr_id("");
        curr_id << std::setfill('0') << std::setw(3) << i;
        curr_filename.replace(
        curr_filename.find("000"), 3, curr_id.str());
        this->frames.push_back(new ModelObject(curr_filename, mtllib));
    }
}

bool Anim::go_on(void)
{
    this->draw();
    return this->frame_inc();
}

void Anim::draw(void)
{
    this->frames[this->curr_frame]->obj_display();
}

bool Anim::frame_inc(void)
{
    if (this->returning)
    {
        this->curr_frame --;
        if (this->curr_frame <= 0)
        {
            this->curr_frame = 0;
            return false;
        }
        return true;
    }
    this->curr_frame ++;
    if (this->use_starting)
    {
        if (this->curr_frame >= this->frame_ending)
        {
            this->curr_frame = this->frame_starting_nr + 1;
        }
    } else {
        this->curr_frame %= this->frame_ending;
    }
    return true;
}

void Anim::set_starting(int starting)
{
    this->frame_starting_nr = starting;
    this->use_starting = true;
}

void Anim::reset(void)
{
    this->curr_frame = 0;
    this->returning = false;
}

