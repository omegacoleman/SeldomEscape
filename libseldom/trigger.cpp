
#include "global.hpp"

#include "game_math.hpp"
#include "trigger.hpp"

bool Trigger::is_trigged(double x, double y, bool checking)
{
    if ((this->mode == check) && (!checking))
    {
        return false;
    }
	double d;
	get_distance(this->x, this->y, x, y, &d);
    if (d <= this->r)
    {
        if (this->mode == walk_by)
        {
            return true;
        }
    }
    return false;
}

