#ifndef NEO3D_H
#define NEO3D_H

#include <SDL.h>
#include <SDL_opengl.h>
#include "geo3d/geo3d.h"

class Neo3d
{
 public:
    /* Init functions */
    static void init(int width, int height, int bpp);
    static void init();

    /* Exit function(s) */
    static void quit();
};

#endif
