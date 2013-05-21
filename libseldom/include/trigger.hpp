
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
    :x(x), y(y), r(r), mode(mode) {};
    virtual bool is_trigged(double x, double y, bool checking);
    virtual void trig(void) {};
    inline void trig_if_ok(double x, double y, bool checking)
    {
        if (this->is_trigged(x, y, checking))
        {
            this->trig();
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
};

class DebugTrigger: public Trigger
{
    public:
    DebugTrigger(double x, double y, double r, TrigMode mode)
    : Trigger(x, y, r, mode), open(true) {};
    inline void trig(void)
    {
        if (this->open)
        {
            debug_log("Debug trigger reached at :");
            debug_log(this->x);
            debug_log(this->y);
            debug_flush();
            this->open = false;
        }
    };
    bool open;
};

#endif


