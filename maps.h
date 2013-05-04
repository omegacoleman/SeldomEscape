

#ifndef _MAPS_H_
#define _MAPS_H_

#include <string>
#include <iostream>
#include "objload.h"


class Land;
class Item;
class GameMap;

class Land
{
    public:
    Land(std::string name);
    double get_z_at(double x, double y);
    private:
    std::vector<double (*)[3]> faces;
};

class Item
{
    public:
    Item(std::string name, double x, double y);
    void draw(GameMap *map);
    inline double get_x(void)
    {
        return this->x;
    };
    inline double get_y(void)
    {
        return this->y;
    };
    private:
    std::string name;
    ModelObject model;
    double x, y;
};

class GameMap
{
    public:
    GameMap(std::string ground_id);
    inline void draw(void)
    {
        this->ground_object.obj_display();
        this->draw_items();
    };
    void try_move_to(double *x, double *y, double *z, 
        const double delta_x, const double delta_y);
    double get_initial_z(const double x, const double y);
    inline void add_item(std::string name, double x, double y)
    {
        this->items.push_back(Item(name, x, y));
    };
    inline double get_z_at(const double x, const double y)
    {
        return this->land.get_z_at(x, y);
    };
    void draw_items(void);
    private:
    Land land;
    std::vector<Item> items;
    ModelObject ground_object;
};

const double not_landed = -500000;

#endif

