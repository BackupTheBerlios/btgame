#ifndef CAMERA_H
#define CAMERA_H

#include "object.h"

class Camera : public Object
{
 public:
    void init();
    void draw(); /* Sets the camera to position */
    void mouseMotion(int x, int y); /* Rotate camera by mouse */
};

#endif
