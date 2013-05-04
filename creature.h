
#ifndef _CREATURE_H_
#define _CREATURE_H_

#include <map>
#include <string>
#include "objload.h"
#include "animloader.h"
#include "maps.h"

const std::string ext_normal("$normal");
const std::string ext_a_running("$running_000");
const std::string ext_m_def("$def");

class Creature
{
    public:
    Creature(std::string name, std::string model_id, GameMap *map);
    void add_action(std::string ext, int fr_nr, int fr_start);
    void draw(void);
    void do_action(std::string ext);
    void move(double delta_x, double delta_y);
    void move_rotated(double angle, double stepsize);
    void camera_this(void);
    private:
    std::string name;
    std::string model_id;
    MTLLibrary mtllib;
    std::map<std::string, Anim*> actions;
    Anim *curr_action;
    Anim *next_action;
    ModelObject normal_object;
    double x, y, z, land_z, r;
    GameMap *map;
};

#endif

