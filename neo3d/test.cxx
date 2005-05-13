#include "neo3d/geo3d/geo3d.h"
#include "neo3d/neo3d.h"
#include "neo3d/object.h"
#include "neo3d/camera.h"
#include "neo3d/trimesh.h"
#include "neo3d/n3dloader.h"

class TestObj : public Object
{
public:
    void draw()
    {
        glPushMatrix();
        glMultMatrixd(mat);
        glBegin(GL_TRIANGLES);
            glColor3f(1.0, 0.0, 0.0); glVertex3f(0.0, 1.0, 0.0);
            glColor3f(0.0, 1.0, 0.0); glVertex3f(1.0, -1.0, 0.0);
            glColor3f(0.0, 0.0, 1.0); glVertex3f(-1.0, -1.0, 0.0);
        glEnd();
        glPopMatrix();
    }
};


int main(int argc, char **argv)
{
    SDL_Event event;
    bool done = false;
    Neo3d::init();

    bool fwrd = false, bckw = false;
    bool rght = false, left = false;

    TriMesh *test;
    test = N3DLoader::loadFile("test.n3d");
    if (test == NULL)
        printf("keine Neo3D-Datei\n");

    /* Colored Triangle Object */
    //    TestObj *triangle = new TestObj();
    vertex setPosition = setVertex(newVertex(), 0.0, 0.0, -1.0, 1.0);
    TriMesh *triangle = new TriMesh();
    triangle->addTriangle(setVertex(newVertex(), 1.0, 0.0, 0.0, 1.0), 
                          setVertex(newVertex(), 0.0, 1.0, 0.0, 1.0),
                          setVertex(newVertex(), 0.0, 1.0, 0.0, 1.0),
                          setVertex(newVertex(), 1.0, -1.0, 0.0, 1.0),
                          setVertex(newVertex(), 0.0, 0.0, 1.0, 1.0),
                          setVertex(newVertex(), -1.0, -1.0, 0.0, 1.0));
    
    triangle->setPos(setPosition);
    triangle->buildMatrix();
    
    /* Initialize camera */
    Camera *cam = new Camera();
    cam->init();
    cam->setPos(setVertex(newVertex(), 0.0, 0.0, 1.0, 1.0));
    cam->setFront(setVertex(newVertex(), 0.0, 0.0, -1.0, 1.0));
    cam->setUp(setVertex(newVertex(), 0.0, 1.0, 0.0, 1.0));
    cam->buildNegMatrix();

    glEnable(GL_CULL_FACE);
    
    while (!done) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                done = true;
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_UP) {
                    fwrd = true;
                 }
                else if (event.key.keysym.sym == SDLK_DOWN) {
                    bckw = true;
                 }
                else if (event.key.keysym.sym == SDLK_LEFT) {
                    left = true;
                }
                else if (event.key.keysym.sym == SDLK_RIGHT) {
                    rght = true;
                }
                else if (event.key.keysym.sym == SDLK_ESCAPE) {
                    done = true;
                }
                else if (event.key.keysym.sym == SDLK_f) {
                    SDL_WM_ToggleFullScreen(SDL_GetVideoSurface());
                }
                else if (event.key.keysym.sym == SDLK_m) {
                    matrix current = newMatrix();
                    glGetDoublev(GL_MODELVIEW_MATRIX, current);
                    printMatrix(current);
                }
                break;
            case SDL_KEYUP:
                if (event.key.keysym.sym == SDLK_UP) {
                    fwrd = false;
                }
                else if (event.key.keysym.sym == SDLK_DOWN) {
                    bckw = false;
                }
                else if (event.key.keysym.sym == SDLK_LEFT) {
                    left = false;
                }
                else if (event.key.keysym.sym == SDLK_RIGHT) {
                    rght = false;
                }
                break;
            case SDL_MOUSEMOTION:
                cam->mouseMotion(320 - event.motion.x, 240 - event.motion.y);
                if (event.motion.x != 320 || event.motion.y != 240)
                    SDL_WarpMouse(320, 240);
                break;
            default:
                break;
            }
        }
        if (fwrd)
            cam->moveForward(.010);
        if (bckw)
            cam->moveForward(-.010);
        if (left)
            cam->moveRight(-.01);
        if (rght)
            cam->moveRight(.01);
        
        //        cam->draw();
        cam->draw();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        test->draw();
        SDL_GL_SwapBuffers();
    }
    
    delete triangle;
    delete test;

    Neo3d::quit();

    return 0;
}
