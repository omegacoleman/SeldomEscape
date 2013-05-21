
#include "global.hpp"

#include "creature.hpp"
#include <cmath>
#include <GL/gl.h>

const double falling_speed = 0.15;

Creature::Creature(std::string name, std::string model_id, 
    GameMap *map, double x, double y, double r)
:name(name), 
    model_id(model_id), 
    mtllib(model_id + ext_m_def), 
    normal_object(model_id + ext_normal, &(this->mtllib)), 
    x(x), y(y), r(r), 
    actions(), 
    curr_action(NULL), 
    map(map)
{
    this->z = this->land_z = this->map->get_z_at(this->x, this->y);
}

void Creature::draw(void)
{
    if (this->z > this->land_z)
    {
        this->z -= falling_speed;
    }
    if (this->z < this->land_z)
    {
        this->z = this->land_z;
    }
    glTranslated(this->x, this->z, this->y);
    glRotated(this->r + 180.0, 0.0, -1.0, 0.0);
    if (this->curr_action == NULL) {
        if (this->next_action != NULL)
        {
            this->curr_action = this->next_action;
            this->next_action = NULL;
        }
        this->normal_object.obj_display();
    } else {
        if (! this->curr_action->go_on())
        {
            this->curr_action = NULL;
        }
    }
    glRotated(this->r + 180.0, 0.0, 1.0, 0.0);
    glTranslated(-this->x, -this->z, -this->y);
}

void Creature::move(double delta_x, double delta_y)
{
    if (! this->move_without_slipping(delta_x, delta_y))
    {
        if (delta_x > delta_y)
        {
            if (! this->move_without_slipping(delta_x, 0))
            {
                this->move_without_slipping(0, delta_y);
            }
        } else {
            if (! this->move_without_slipping(0, delta_y))
            {
                this->move_without_slipping(delta_x, 0);
            }
        }
    }
}

bool Creature::move_without_slipping(double delta_x, double delta_y)
{
    bool result = this->map->try_move_to(
        &(this->x), &(this->y), &(this->land_z), 
        delta_x, delta_y);
    if (this->z < this->land_z)
    {
        this->z = this->land_z;
    }
    return result;
}

void Creature::move_rotated(double angle, double stepsize)
{
    this->move(
        +sin(angle * PI / 180.0) * stepsize, 
        -cos(angle * PI / 180.0) * stepsize);
    if ((angle - this->r) > 180.0)
    {
        this->r += 360.0;
    } else if((angle - this->r) < -180.0) {
        this->r -= 360.0;
    }
    this->r += (angle - this->r) / 3;
}

void Creature::add_action(std::string ext, int fr_nr, int fr_start)
{
    this->actions[ext] = new Anim(this->model_id + ext, fr_nr, &(this->mtllib));
    if (fr_start != 0)
    {
        this->actions[ext]->set_starting(fr_start);
    }
}

void Creature::do_action(std::string ext)
{
    if (ext != "")
    {
        if (this->actions[ext] == this->curr_action)
        {
            return;
        } else {
            this->next_action = this->actions[ext];
            this->next_action->reset();
        }
    } else {
        this->next_action = NULL;
    }
    if (this->curr_action != NULL)
    {
        this->curr_action->return_now();
    }
}

void Creature::camera_this(void)
{
    glTranslated(-this->x, -this->z, -this->y);
}

