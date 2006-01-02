#include "neo3d.h"
#include "textureStack.h"

void Neo3d::init(int width, int height, int bpp, char *texPath)
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
    texStack = new TextureStack();
    texStack->setPath(texPath);
    glEnable(GL_TEXTURE_2D); 
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_CULL_FACE);


    /* Init Geo3d */
    initGeo3d();
}

void Neo3d::init(char *texPath)
{
    Neo3d::init(640, 480, 16, texPath);
}

void Neo3d::quit()
{
    SDL_Quit();
}
