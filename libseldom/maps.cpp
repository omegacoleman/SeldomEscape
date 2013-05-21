
#include "global.hpp"
#include <cstdlib>
#include <GL/gl.h>

#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include "game_math.hpp"
#include "maps.hpp"

const std::string dot_land(".land");

GameMap::GameMap(std::string ground_id)
:land(ground_id), ground_object(ground_id), items(), triggers()
{
}

bool GameMap::try_move_to(double *x, double *y, double *z, 
    const double delta_x, const double delta_y)
{
    double target_x = *x + delta_x;
    double target_y = *y + delta_y;
    double target_z = this->land.get_z_at(target_x, target_y);
    double delta_z = target_z - *z;
    if ((delta_z <= 0.7) && (delta_z >= -0.7))
    {
        *x = target_x;
        *y = target_y;
        *z = target_z;
        return true;
    }
    return false;
}

double GameMap::get_initial_z(const double x, const double y)
{
    return this->land.get_z_at(x, y);
}

Land::Land(std::string name)
{
    std::ifstream file((res_dir + dollar_to_sep(name) + dot_land).c_str());
    std::string in;
    std::vector<double *> v;
    if (! file.good())
    {
        aborting("Can't read landscape : " + name);
    }
    while (file.good())
    {
        file >> in;
        if (in == "v")
        {
            std::string sx, sy, sz;
            file >> sx >> sy >> sz;
            v.push_back(new double[3]);
            v.back()[0] = atof(sx.c_str());
            v.back()[1] = atof(sy.c_str());
            v.back()[2] = atof(sz.c_str());
        } else if (in == "f")
        {
            int n = 0;
            this->faces.push_back(new double[3][3]);
            for (n = 0; n < 3; n++)
            {
                file >> in;
                const int curr_v = atoi(in.c_str()) - 1;
                this->faces.back()[n][0] = v[curr_v][0];
                this->faces.back()[n][1] = v[curr_v][2];
                this->faces.back()[n][2] = v[curr_v][1];
            }
        }
    }
}

double Land::get_z_at(double x, double y)
{
    std::vector<double (*)[3]>::iterator iter;
    for (iter = this->faces.begin(); iter != this->faces.end(); iter++)
    {
        if (in_2d_triangle(x, y, 
            (*iter)[0][0], (*iter)[0][1], 
            (*iter)[1][0], (*iter)[1][1], 
            (*iter)[2][0], (*iter)[2][1]))
        {
            double a, b, c, d;
            get_face_abcd(*iter, &a, &b, &c, &d);
            return ((-a*x-b*y-d)/c);
        }
    }
    return not_landed;
}

Item::Item(std::string name, double x, double y)
:name(name), model(name), x(x), y(y)
{
}

void Item::draw(GameMap *map)
{
    double x = this->get_x();
    double y = this->get_y();
    double z = map->get_z_at(x, y);
    glTranslated(x, z, y);
    this->model.obj_display();
    glTranslated(-x, -z, -y);
}

void GameMap::draw_items(void)
{
    std::vector<Item>::iterator iter;
    for (iter = this->items.begin(); iter != this->items.end(); iter++)
    {
        iter->draw(this);
    }
}


