#include "neo3d.h"

void Neo3d::init(int width, int height, int bpp)
{
    /* Init SDL */
    SDL_Init(SDL_INIT_VIDEO);
    SDL_SetVideoMode(width, height, bpp, SDL_OPENGL);
    
    /* Init OpenGL */
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLdouble)width/(GLdouble)height, .01, 200.0);
    glMatrixMode(GL_MODELVIEW);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);

    /* Init Geo3d */
    initGeo3d();
}

void Neo3d::init()
{
    Neo3d::init(640, 480, 16);
}

void Neo3d::quit()
{
    SDL_Quit();
}
