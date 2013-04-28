
#include "global.h"
#include "animloader.h"
#include "objload.h"

#include <string>
#include <sstream>
#include <iomanip>

Anim::Anim(std::string basename, int frames_nr, MTLLibrary *mtllib)
:frame_ending(frames_nr), frames(), curr_frame(0)
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

void Anim::go_on(void)
{
    this->draw();
    this->frame_inc();
}

void Anim::draw(void)
{
    this->frames[this->curr_frame]->obj_display();
}

void Anim::frame_inc(void)
{
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
}

void Anim::set_starting(int starting)
{
    this->frame_starting_nr = starting;
    this->use_starting = true;
}

