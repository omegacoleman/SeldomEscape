
#ifndef _TRIGGER_HPP_
#define _TRIGGER_HPP_

#include "debug_output.hpp"

enum TrigMode
{
    walk_by, 
    check,
};

class Trigger
{
    public:
    Trigger(double x, double y, double r, TrigMode mode) 
    :x(x), y(y), r(r), mode(mode), 
    should_call_trig(true) {};
    virtual bool is_trigged(double x, double y, bool checking);
    virtual void trig(void) {};
    virtual void leave(void) {};
    inline void trig_if_ok(double x, double y, bool checking)
    {
        if (this->is_trigged(x, y, checking))
        {
            if (should_call_trig)
            {
                this->trig();
                should_call_trig = false;
            }
        } else {
            if (! should_call_trig)
            {
                this->leave();
                should_call_trig = true;
            }
        }
    };
    inline virtual double get_x(void)
    {
        return this->x;
    };
    inline virtual double get_y(void)
    {
        return this->y;
    };
    inline virtual double get_size(void)
    {
        return this->r;
    };
    protected:
    double x, y, r;
    TrigMode mode;
    bool should_call_trig;
};

class DebugTrigger: public Trigger
{
    public:
    DebugTrigger(double x, double y, double r, TrigMode mode)
    : Trigger(x, y, r, mode) {};
    inline void trig(void)
    {
        debug_log("Debug trigger reached at :");
        debug_log(this->x);
        debug_log(this->y);
        debug_flush();
    };
};

template <class T> class CameraTrigger: public Trigger
{
    public:
    CameraTrigger(double x, double y, double r, double t, T *camera)
    : Trigger(x, y, r, walk_by), camera(camera), target(t),
    orig(camera->get_angle()) {};
    inline void trig(void)
    {
        this->orig = this->camera->get_angle();
        this->camera->turn_abs(this->target);
    };
    inline void leave(void)
    {
        this->camera->turn_abs(this->orig);
    };
    private:
    T* camera;
    double target;
    double orig;
};

#endif


