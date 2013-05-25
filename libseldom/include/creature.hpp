
#ifndef _CREATURE_H_
#define _CREATURE_H_

#include "global.hpp"

#include "maps.hpp"
#include "load_obj.hpp"
#include "load_anim.hpp"
#include <map>
#include <string>

#ifdef __DEBUG
#include <iostream>
#include "debug_output.hpp"
#endif

const std::string ext_normal("$normal");
const std::string ext_a_running("$running_000");
const std::string ext_m_def("$def");

class Creature
{
    public:
    Creature(std::string name, std::string model_id, 
        GameMap *map, double x=0.0, double y=0.0, double r=0.0);
    void add_action(std::string ext, int fr_nr, int fr_start);
    void draw(void);
    void do_action(std::string ext);
    void move(double delta_x, double delta_y);
    void move_rotated(double angle, double stepsize);
    void camera_this(void);
    bool move_without_slipping(double delta_x, double delta_y);
    #ifdef __DEBUG
    void dump_debug()
    {
        debug_log("NAME : " + this->name);
        debug_log("X : ");debug_log(this->x);
        debug_log("Y : ");debug_log(this->y);
        debug_log("R : ");debug_log(this->r);
        debug_flush();
    };
    #endif
    inline double get_x(void)
    {
        return this->x;
    };
    inline double get_y(void)
    {
        return this->y;
    };
    inline double get_z(void)
    {
        return this->z;
    };
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

