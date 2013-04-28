
#include "global.h"
#include "basegl.h"
#include "image_loading.h"

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#include "objload.h"

#include <stdlib.h>
#include <GL/gl.h>

const std::string dot_obj(".obj");
const std::string dot_mtl(".mtl");

ModelObject::ModelObject(std::string name)
{
    this->init(dollar_to_sep(name), NULL);
}

ModelObject::ModelObject(std::string name, MTLLibrary *mlib)
{
    this->init(dollar_to_sep(name), mlib);
}

void ModelObject::init(std::string name, MTLLibrary *mlib)
{
    std::ifstream file((res_dir + name + dot_obj).c_str());
    std::string in;
    if (! file.good())
    {
        aborting("Can't read model : " + name);
    }
    this->gl_list = glGenLists(1);
    glNewList(this->gl_list, GL_COMPILE);
    this->mtllib = mlib;
    while (file.good())
    {
        file >> in;
        SIGN_PROCESS:
        if (in == "v")
        {
            std::string sx, sy, sz;
            file >> sx >> sy >> sz;
            this->v.push_back(std::vector<double>());
            this->v.back().push_back(atof(sx.c_str()));
            this->v.back().push_back(atof(sy.c_str()));
            this->v.back().push_back(atof(sz.c_str()));
        } else if (in == "vt")
        {
            std::string sx, sy;
            file >> sx >> sy;
            this->vt.push_back(std::vector<double>());
            this->vt.back().push_back(atof(sx.c_str()));
            this->vt.back().push_back(atof(sy.c_str()));
        } else if (in == "f")
        {
            glBegin(GL_POLYGON);
            while (! file.eof())
            {
                file >> in;
                if (in.find("/") != std::string::npos)
                {
                    std::istringstream iss(in);
                    std::string curr_v_s;
                    std::string curr_tex_s;
                    getline(iss, curr_v_s, '/');
                    getline(iss, curr_tex_s, '/');
                    int curr_v = atoi(curr_v_s.c_str()) - 1;
                    int curr_tex = atoi(curr_tex_s.c_str()) - 1;
                    glTexCoord2d(this->vt[curr_tex][0], 
                        this->vt[curr_tex][1]);
                    glVertex3d(this->v[curr_v][0], 
                        this->v[curr_v][1], 
                        this->v[curr_v][2]);
                } else if (atoi(in.c_str()) != 0)
                {
                    const int curr_v = atoi(in.c_str()) - 1;
                    glVertex3d(this->v[curr_v][0], 
                        this->v[curr_v][1], 
                        this->v[curr_v][2]);
                } else {
                    glEnd();
                    goto SIGN_PROCESS;
                }
            }
            glEnd();
        } else if (in == "mtllib")
        {
            if (mlib == NULL)
            {
                std::string mtlfname;
                file >> mtlfname;
                mtlfname = name.substr(0, name.find_last_of(path_sep) + 1) + mtlfname;
                this->mtllib = new MTLLibrary(mtlfname);
            }
        } else if (in == "usemtl")
        {
            std::string mat_n;
            file >> mat_n;
            this->mtllib->get_material(mat_n)->switch_to();
        }
    }
	glEndList();
}

void ModelObject::obj_display(void)
{
    glCallList(this->gl_list);
}

MTLLibrary::MTLLibrary(std::string name)
{
    std::ifstream file( \
    (res_dir + dollar_to_sep(name) + dot_mtl).c_str());
    std::string in;
    if (! file.good())
    {
        aborting("Can't read materail library : " + name);
    }
    while (file.good())
    {
        file >> in;
        if (in == "newmtl")
        {
            std::string name;
            file >> name;
            this->materials.push_back(Material(name));
        } else if (in == "Kd")
        {
            std::string sr, sg, sb;
            file >> sr;
            file >> sg;
            file >> sb;
            this->materials.back().set_diffuse(
                atof(sr.c_str()), 
                atof(sg.c_str()), 
                atof(sb.c_str()));
        } else if (in == "map_Kd")
        {
            std::string tex_image;
            file >> tex_image;
            in = "";
            this->materials.back().set_texture(tex_image);
        }
    }
}

Material *MTLLibrary::get_material(const std::string name)
{
    std::vector<Material>::iterator iter;
    for (iter = this->materials.begin();
        iter != this->materials.end();
        iter++)
    {
        if ((*iter) == name)
        {
            return &(*iter);
        }
    }
    aborting("Unfinded material : " + name);
    // Never reached.
    return NULL;
}

Material::Material(std::string m_name)
:name(m_name), is_using_texture(false)
{
}

void Material::set_diffuse(const double r, const double g, const double b)
{
    this->diffuse.clear();
    this->diffuse.push_back(r);
    this->diffuse.push_back(g);
    this->diffuse.push_back(b);
}

void Material::set_texture(const std::string filename)
{
    this->is_using_texture = true;
    this->texture = get_texture(filename);
}

void Material::switch_to(void)
{
    if (this->is_using_texture)
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, this->texture);
    } else
    {
        glDisable(GL_TEXTURE_2D);
    }
    glColor3d(this->diffuse[0], this->diffuse[1], this->diffuse[2]);
}

