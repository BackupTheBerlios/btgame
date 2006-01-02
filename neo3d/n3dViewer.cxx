#include "neo3d/neo3d.h"
#include "neo3d/camera.h"
#include "neo3d/blobeffect.h"
#include "neo3d/n3dloader.h"
#include <SDL_mixer.h>

/*#define W 1280
  #define H 1024  */ 

#define W 1024
#define H 768

int main(int argc, char **argv)
{
    SDL_Event event;
    bool done = false; /* if true gameloop is exiting */
    bool fwrd = false, bckw = false; /* keypress events */
    bool rght = false, left = false;
    bool tUp = false, tDown= false; /* Turn around */
    bool tLeft = false, tRight = false;
    bool bindMouse = false;

    /* Initialize Neo3d */
    Neo3d::init(W, H, 0, "data");
    SDL_InitSubSystem(SDL_INIT_AUDIO);
    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096);
    Mix_Music *music = Mix_LoadMUS("music.mod");
    Mix_FadeInMusic(music, -1, 4000);

    /* Loading object and let it blob */
    DrawObject *test = N3DLoader::load(argv[1]);
    test = new BlobEffect(test,                   /* To overwrite test is not nice but it works ;) */
			  setVertex(newVertex(), 0.0, 0.0, 1.0, 0.0), 
			  1.0, 0.25); 

    /* Initialize camera */
    Camera *cam = new Camera();
    cam->init();
    cam->setPos(setVertex(newVertex(), 0.0, -5.0, 0.0, 1.0));
    cam->setFront(setVertex(newVertex(), 0.0, 1.0, 0.0, 1.0));
    cam->setUp(setVertex(newVertex(), 0.0, 0.0, 1.0, 1.0));

    SDL_WarpMouse(W/2, H/2);
    while (!done) {
      SDL_Delay(10);
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                done = true;
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_w) {
                    fwrd = true;
                 }
                else if (event.key.keysym.sym == SDLK_s) {
                    bckw = true;
                 }
                else if (event.key.keysym.sym == SDLK_a) {
                    left = true;
                }
                else if (event.key.keysym.sym == SDLK_d) {
                    rght = true;
                }
                else if (event.key.keysym.sym == SDLK_UP) {
                     tUp = true;
                }
                else if (event.key.keysym.sym == SDLK_DOWN) {
                     tDown = true;
                }
                else if (event.key.keysym.sym == SDLK_LEFT) {
                     tLeft = true;
                }
                else if (event.key.keysym.sym == SDLK_RIGHT) {
                     tRight = true;
                }
                else if (event.key.keysym.sym == SDLK_ESCAPE) {
                    done = true;
                }
                else if (event.key.keysym.sym == SDLK_f) {
                    SDL_WM_ToggleFullScreen(SDL_GetVideoSurface());
                    SDL_WarpMouse(320, 240);
                }
                else if (event.key.keysym.sym == SDLK_m) {
                    matrix current = newMatrix();
                    glGetDoublev(GL_MODELVIEW_MATRIX, current);
                    printMatrix(current);
                }
                else if (event.key.keysym.sym == SDLK_SPACE) 
                     bindMouse = !bindMouse;
                break;
            case SDL_KEYUP:
                if (event.key.keysym.sym == SDLK_w) {
                    fwrd = false;
                }
                else if (event.key.keysym.sym == SDLK_s) {
                    bckw = false;
                }
                else if (event.key.keysym.sym == SDLK_a) {
                    left = false;
                }
                else if (event.key.keysym.sym == SDLK_d) {
                    rght = false;
                }
                else if (event.key.keysym.sym == SDLK_UP) {
                     tUp = false;
                }
                else if (event.key.keysym.sym == SDLK_DOWN) {
                     tDown = false;
                }
                else if (event.key.keysym.sym == SDLK_LEFT) {
                     tLeft = false;
                }
                else if (event.key.keysym.sym == SDLK_RIGHT) {
                     tRight = false;
                }
                break;
            case SDL_MOUSEMOTION:
                 if (bindMouse) {
	      if ((event.motion.x != W/2 || event.motion.y != H/2)) {
                    SDL_WarpMouse(W/2, H/2);
		    cam->mouseMotion(W/2 - event.motion.x, H/2 - event.motion.y);
	      }
       }
                break;
            default:
                break;
            }
        }
        if (fwrd)
            cam->moveForward(.10);
        if (bckw)
            cam->moveForward(-.10);
        if (left)
            cam->moveRight(-.1);
        if (rght)
            cam->moveRight(.1);
        if (tDown) 
            cam->mouseMotion(0, -3);
        if (tUp) 
            cam->mouseMotion(0, 3);
        if (tRight) 
            cam->mouseMotion(-3, 0);
        if (tLeft) 
            cam->mouseMotion(3, 0);
        if (!tDown) 
            cam->mouseMotion(0, 0);
        if (!tUp) 
            cam->mouseMotion(0, 0);
        if (!tRight) 
            cam->mouseMotion(0, 0);
        if (!tLeft) 
            cam->mouseMotion(0, 0);



	/* Display */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        cam->draw(); /* Camera must be drawn at first */
	test->draw();
        SDL_GL_SwapBuffers();
    }
    
    /* Cleaning up */
    Mix_FadeOutMusic(2000);
    SDL_Delay(2000);
    delete test;

    Neo3d::quit();

    return 0;
} 
