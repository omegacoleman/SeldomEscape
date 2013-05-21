

#ifndef _OBJLOAD_HPP_
#define _OBJLOAD_HPP_

#include "global.hpp"

#include <GL/gl.h>
#include <string>
#include <vector>

class Material
{
    public:
    Material(std::string m_name);
    void set_diffuse(const double r, const double g, const double b);
    bool operator==(const std::string &t1) const {
        return (t1 == this->name);
    }
    void switch_to(void);
    void set_texture(const std::string filename);
    private:
    std::vector<double> diffuse;
    std::string name;
    bool is_using_texture;
    GLuint texture;
};

class MTLLibrary
{
    public:
    MTLLibrary(std::string name);
    Material *get_material(const std::string name);
    private:
    std::vector<Material> materials;
};

class ModelObject
{
    public:
    ModelObject(std::string name);
    ModelObject(std::string name, MTLLibrary *mlib);
	void obj_display(void);
    private:
    void init(std::string name, MTLLibrary *mlib);
    GLuint gl_list;
    std::vector<std::vector<double> > v;
    std::vector<std::vector<double> > vt;
    MTLLibrary *mtllib;
};

#endif

