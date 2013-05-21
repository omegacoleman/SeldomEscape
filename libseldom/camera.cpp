
#include "global.hpp"

#include "camera.hpp"
#include "creature.hpp"
#include <cmath>
#include <GL/gl.h>

const double rot_y_max(15.0);
const double rot_y_min(0.0);
const double rot_y_stepsize(1.2);

const double distance_max(5.0);
const double distance_min(3.0);

const double distance_default(5.0);
const double distance_stepsize(0.5);

const double rot_z_default(0.0);
const double rot_y_default(15.0);

OffsetCamera::OffsetCamera(void)
:rot_z(rot_z_default), rot_y(rot_y_default), distance(distance_default)
{
}

OffsetCamera::OffsetCamera(double rot_z, double rot_y, double distance)
:rot_z(rot_z), rot_y(rot_y), distance(distance)
{
}

void OffsetCamera::set_up(Creature *target)
{
    glTranslated(0.0, -5.0, 0.0);
    glRotated(this->rot_y, 1.0, 0.0, 0.0);
    glTranslated(0.0, 0.0, -this->distance);
    glRotated(this->rot_z, 0.0, 1.0, 0.0);
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

void OffsetCamera::turn(double delta)
{
    this->rot_z += delta;
    while (this->rot_z >= 360.0)
    {
        this->rot_z -= 360.0;
    }
    while (this->rot_z < 0.0)
    {
        this->rot_z += 360.0;
    }
}


