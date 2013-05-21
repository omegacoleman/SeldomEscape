
#ifndef _IMAGE_LOADING_HPP_
#define _IMAGE_LOADING_HPP_

#include "global.hpp"

#include <GL/gl.h>
#include <map>
#include <string>

/**
 * Load all the images need in path_images.
 * 
 * Need a ls.txt, listing all images needed.
 * 
 */
void load_images(void);
/**
 * Return the texture id loaded whose 
 * texture match the name.
 */
GLuint get_texture(std::string name);


#endif


