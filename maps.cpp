
#include "global.h"
#include "stdlib.h"

#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include "game_math.h"
#include "maps.h"

const std::string dot_land(".land");

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
        SIGN_PROCESS:
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
                /**
                this->faces.back().push_back(std::vector<double>());
                this->faces.back().back().push_back(v[curr_v][0]);
                this->faces.back().back().push_back(v[curr_v][2]);
                this->faces.back().back().push_back(v[curr_v][1]);
                **/
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



