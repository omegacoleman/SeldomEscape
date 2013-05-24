
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "creature.hpp"

const double rot_y_max(15.0);
const double rot_y_min(0.0);
const double rot_y_stepsize(1.2);

const double distance_max(5.0);
const double distance_min(3.0);

const double distance_default(5.0);
const double distance_stepsize(0.5);

const double rot_z_default(0.0);
const double rot_y_default(15.0);

class OffsetCamera
{
    public:
    OffsetCamera(double rot_z = rot_z_default, 
    double rot_y = rot_y_default, 
    double distance = distance_default);
    template <class T> void set_up(T *target)
    {
        if ((this->target_rot_z - this->rot_z) > 180.0)
        {
            this->rot_z += 360.0;
        } else if((this->target_rot_z - this->rot_z) < -180.0) {
            this->rot_z -= 360.0;
        }
        this->rot_z += (this->target_rot_z - this->rot_z) / 9;
        glTranslated(0.0, -5.0, 0.0);
        glRotated(this->rot_y, 1.0, 0.0, 0.0);
        glTranslated(0.0, 0.0, -this->distance);
        glRotated(this->rot_z, 0.0, 1.0, 0.0);
        target->camera_this();
    };
    inline double get_angle(void)
    {
        return this->target_rot_z;
    };
    inline double get_real_angle(void)
    {
        return this->rot_z;
    };
    void upper(void);
    void lower(void);
    void farther(void);
    void nearer(void);
    void turn(double delta);
    void turn_abs(double target);
    private:
    double rot_z, rot_y, distance;
    double target_rot_z;
};

#endif


