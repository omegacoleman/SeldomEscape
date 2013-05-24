
#include "global.hpp"

#include "camera.hpp"
#include "creature.hpp"
#include <cmath>
#include <GL/gl.h>

OffsetCamera::OffsetCamera(double rot_z, double rot_y, double distance)
:rot_z(rot_z), rot_y(rot_y), distance(distance), target_rot_z(rot_z)
{
}

void OffsetCamera::upper(void)
{
    this->rot_y += rot_y_stepsize;
    if (this->rot_y > rot_y_max)
    {
        this->rot_y = rot_y_max;
    }
}

void OffsetCamera::lower(void)
{
    this->rot_y -= rot_y_stepsize;
    if (this->rot_y < rot_y_min)
    {
        this->rot_y = rot_y_min;
    }
}

void OffsetCamera::farther(void)
{
    this->distance += distance_stepsize;
    if (this->distance > distance_max)
    {
        this->distance = distance_max;
    }
}

void OffsetCamera::nearer(void)
{
    this->distance -= distance_stepsize;
    if (this->distance < distance_min)
    {
        this->distance = distance_min;
    }
}

void OffsetCamera::turn_abs(double target)
{
    this->target_rot_z = target;
    while (this->target_rot_z >= 360.0)
    {
        this->target_rot_z -= 360.0;
    }
    while (this->target_rot_z < 0.0)
    {
        this->target_rot_z += 360.0;
    }
}

void OffsetCamera::turn(double delta)
{
    this->target_rot_z += delta;
    while (this->target_rot_z >= 360.0)
    {
        this->target_rot_z -= 360.0;
    }
    while (this->target_rot_z < 0.0)
    {
        this->target_rot_z += 360.0;
    }
}


