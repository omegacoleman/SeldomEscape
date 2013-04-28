

#ifndef _MAPS_H_
#define _MAPS_H_

class Land
{
    public:
    Land(std::string name);
    double get_z_at(double x, double y);
    // void draw(void);
    private:
    std::vector<double (*)[3]> faces;
};

/**
class GameMap
{
    public:
    void draw(void);
    private:
    Land land;
};
**/

const double not_landed = -123.0;

#endif

