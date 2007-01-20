#ifndef OBJECT_H
#define OBJECT_H

#include <AL/al.h>
#include <AL/alut.h>

#include "neo3d.h"
#include "string.h"

class Object
{
 protected:
    vertex pos; /* Position of an object */
    vertex front; /* Vector to the front of this object (normalized) */
    vertex up; /* Vector to the top of this object (normalized) */
    vertex right; /* Vector to the side of this object (just calculated) */
    matrix mat; /* Contains everything of an object */
    bool hasAudio; /* can object make sounds? */
    ALuint source; /* source for OpenAL */

 public:
    /* Init and deinit */
    Object();
    ~Object(); /* If you don't need an instance any more
                  USE delete instancename; ! */
    void init(vertex pos, vertex front, vertex up);

    /* Get methods */
    vertex getPos(vertex ver);     /* a pointer to the position */
    vertex getFront(vertex ver);   /* a pointer to the front vector */
    vertex getUp(vertex ver);      /* a pointer to the up vector */
    matrix getMatrix(matrix mat);  /* a pointer to the matrix vector */

    /* Set methods */
    void setPos(vertex ver);     /* set position */
    void setFront(vertex ver);   /* set front vector */
    void setUp(vertex ver);      /* set up vector */

    /* move methods */
    void moveForward(GLdouble length); /* To move the object to front */
    void moveRight(GLdouble length);   /* To move the object right */

    /* misc */
    void buildMatrix(); /* build the matrix using up, front and pos-vector */
    void buildNegMatrix(); /* build the negativ matrix using up, front and 
                           pos-vector (useful for camera) */
    void multMatrix(matrix mat, matrix buffer);

    /* audio options */
    void startAudio();
};

#endif
