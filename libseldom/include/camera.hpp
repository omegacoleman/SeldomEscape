
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "creature.hpp"

class OffsetCamera
{
    public:
    OffsetCamera(void);
    OffsetCamera(double rot_z, double rot_y, double distance);
    void set_up(Creature *target);
    inline double get_angle(void)
    {
        return this->rot_z;
    };
    void upper(void);
    void lower(void);
    void farther(void);
    void nearer(void);
    void turn(double delta);
    private:
    double rot_z, rot_y, distance;
};

#endif


