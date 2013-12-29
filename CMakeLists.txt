
cmake_minimum_required(VERSION 2.6)
cmake_policy(VERSION 2.6)
project(SeldomEscape)

SET(CMAKE_BUILD_TYPE "Debug") 

include(FindSDL)
include(FindSDL_image)
include(FindOpenGL)

link_libraries(${SDL_LIBRARY} ${SDLIMAGE_LIBRARY} ${OPENGL_LIBRARIES})


include_directories(${SeldomEscape_SOURCE_DIR}/libseldom/include/)
include_directories(${SeldomEscape_SOURCE_DIR}/liblower/include/)
include_directories(${SeldomEscape_SOURCE_DIR}/libloaders/include/)
add_library(seldom libseldom/camera.cpp libseldom/camera.cpp libseldom/maps.cpp libseldom/creature.cpp libseldom/game_math.cpp libseldom/trigger.cpp)
add_library(lower liblower/base_gl.cpp liblower/base_sdl.cpp liblower/debug_output.cpp liblower/ending.cpp)
add_library(loaders libloaders/load_anim.cpp libloaders/load_image.cpp libloaders/load_obj.cpp libloaders/load_text.cpp)
link_libraries(seldom lower loaders)
add_executable(SE se_main.cpp)
