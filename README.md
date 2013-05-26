

SeldomEscape
============


Intro
-----

Seldom Escape is a developing 3d C++ game using OpenGL &amp; SDL.

It now(05262013) contians three static libs :
* liblower
* libloaders
* libseldom
and a main file.


Well, if you are only a player and cares nothing about programming, keep out until the June comes..

Building
--------

First things first, if you haven't installed OpenGL, SDL and its
devel packages, install them first:

On ubuntu:
    sudo apt-get install libsdl1.2-dev libsdl-image1.2-dev
    sudo apt-get install libglu1-mesa-dev freeglut3-dev mesa-common-dev

On fedora(Or most of other EL based linux):
    yum install SDL-devel SDL_image-devel
    yum install mesa-libGL-devel mesa-libGLU-devel mesa-libGLw-devel mesa-libOSMesa-devel
    # The last one is not needed in most of situations.

On windows, you need to download:

* [Devel pack of SDL](http://www.libsdl.org/release/SDL-devel-1.2.15-VC.zip)
* [and SDL_image](http://www.libsdl.org/projects/SDL_image/release/SDL_image-devel-1.2.12-VC.zip)

And install them to VC++

Then, run these commands on linux:
    mkdir build
    cd build
    ln -s ../res .
    cmake ..
    make

On windows just run the batch file. Press enter for times.

Then you'll get the game in "build/" on Linux, "VC/Final/" on windows!

Playing
-------

You can just run everywhere in the map in this version with WASD,
And IJKL is for viewport operations.

Press ESC to close the game.






