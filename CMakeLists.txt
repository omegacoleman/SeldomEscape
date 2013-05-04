
cmake_minimum_required(VERSION 2.8)
project(MyPark)

SET(CMAKE_BUILD_TYPE "Debug") 

include(FindSDL)
include(FindSDL_image)
include(FindOpenGL)
include(FindGLU)

link_libraries(${SDL_LIBRARY} ${SDLIMAGE_LIBRARY} ${GL_LIBRARY} ${GLU_LIBRARY})

add_executable(MyPark main.cpp ending.cpp objload.cpp basegl.cpp basesdl.cpp image_loading.cpp animloader.cpp game_math.cpp maps.cpp creature.cpp)

