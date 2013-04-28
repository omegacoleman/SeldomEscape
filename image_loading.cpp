
#include "global.h"
#include <GL/gl.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <map>
#include <fstream>
#include <string>


static GLuint load_image_as_texture(const std::string filename);

static const std::string path_images("./res/images/");

static std::map<std::string, GLuint> image_map;

void load_images(void)
{
    std::ifstream file_ls((path_images + "ls.txt").c_str());
    if (! file_ls.good())
    {
        aborting("LS file not found in " + path_images);
    }
    while (file_ls.good())
    {
        std::string in;
        file_ls >> in;
        if (in != "")
        {
            image_map[in] = load_image_as_texture(path_images + in);
        }
    }
}

GLuint get_texture(std::string name)
{
    if (image_map.count(name) > 0)
    {
        return image_map[name];
    } else {
        aborting("Texture not found : " + name);
    }
}


GLuint load_image_as_texture(const std::string filename)
{
    GLuint texture;
    SDL_Surface *image;
    image = IMG_Load(filename.c_str());
    if(!image) {
        aborting((std::string)
            "Image load failed: " + SDL_GetError());
    }
    glEnable(GL_TEXTURE_2D);
    glMatrixMode(GL_TEXTURE);
    glLoadIdentity();
    // The images loaded is up-to-down in GL.
    glScalef(1.0f, -1.0f, 1.0f);
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // BytesPerPixel : 3 stands for RGB, 4 stands for RGBA
    // Index coloring and other formats NOT supported.
    if (image->format->BytesPerPixel == 3) {
        glTexImage2D(GL_TEXTURE_2D, 0, 3, image->w, image->h, 
            0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
    } else if (image->format->BytesPerPixel == 4) {
        glTexImage2D(GL_TEXTURE_2D, 0, 4, image->w, image->h, 
            0, GL_RGBA, GL_UNSIGNED_BYTE, image->pixels);
    } else {
        aborting((std::string) 
            "Unsupported image format : " + filename);
    }
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    return texture;
}



