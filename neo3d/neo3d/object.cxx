#include "object.h"

/**** Init functions ****/

/* Constructor if no position is given */
Object::Object()
{
    pos = setVertex(newVertex(), 0.0, 0.0, 0.0, 1.0);
    front = setVertex(newVertex(), 0.0, 0.0, -1.0, 1.0);
    up = setVertex(newVertex(), 0.0, 1.0, 0.0, 1.0);
    
    init(pos, front, up);
}

/* Free memory */
Object::~Object()
{
    free(pos);
    free(front);
    free(up);
    free(mat);
}

/* Real init-function */
void Object::init(vertex pos, vertex front, vertex up)
{
    this->pos = pos;
    this->front = front;
    this->up = up;
    this->right = newVertex();
    this->mat = newMatrix();
    buildMatrix();
}

/**** Getter functions ****/
vertex Object::getPos(vertex ver)
{
    ver = (vertex) memcpy(ver, pos, sizeof(GLdouble) * 4);
    return ver;
}

vertex Object::getFront(vertex ver)
{
    ver = (vertex) memcpy(ver, front, sizeof(GLdouble) * 4);
    return ver;
}

vertex Object::getUp(vertex ver)
{
    ver = (vertex) memcpy(ver, up, sizeof(GLdouble) * 4);
    return ver;
}

vertex Object::getMatrix(matrix mat)
{
    mat = (matrix) memcpy(mat, this->mat, sizeof(GLdouble) * 16);
    return mat;
}


/**** Setter functions ****/
void Object::setPos(vertex ver)
{
    memcpy(pos, ver, sizeof(GLdouble) * 4);
}

void Object::setFront(vertex ver)
{
    memcpy(front, ver, sizeof(GLdouble) * 4);
}

void Object::setUp(vertex ver)
{
    memcpy(up, ver, sizeof(GLdouble) * 4);
}


/**** move methods ****/
void Object::moveForward(GLdouble length)
{
    GLdouble buffer[4];
    multVertex(buffer, front, length);
    addVertex(pos, pos, buffer);
}

void Object::moveRight(GLdouble length)
{
    GLdouble buffer[4];
    vertexXvertex(right, front, up);
    multVertex(buffer, right, length);
    addVertex(pos, pos, buffer);
}

/**** misc ****/
void Object::buildMatrix()
{
    vertexXvertex(right, front, up);

    /* UP */
    mat[4] = up[0];
    mat[5] = up[1];
    mat[6] = up[2];

    /* Front */
    mat[8] = -front[0];
    mat[9] = -front[1];
    mat[10] = -front[2];

    /* Right */
    mat[0] = right[0];
    mat[1] = right[1];
    mat[2] = right[2];

    /* Position */
    mat[12] = pos[0];
    mat[13] = pos[1];
    mat[14] = pos[2];
    
    /* Border row */
    mat[3] = 0.0;
    mat[7] = 0.0;
    mat[11] = 0.0;
    mat[15] = 1.0;
}

void Object::buildNegMatrix()
{
    vertexXvertex(right, front, up);

    /* UP */
    mat[4] = up[0];
    mat[5] = up[1];
    mat[6] = up[2];

    /* Front */
    mat[8] = front[0];
    mat[9] = front[1];
    mat[10] = front[2];

    /* Right */
    mat[0] = right[0];
    mat[1] = right[1];
    mat[2] = right[2];

    /* Position */
    mat[12] = -pos[0];
    mat[13] = -pos[1];
    mat[14] = -pos[2];
    
    /* Border row */
    mat[3] = 0.0;
    mat[7] = 0.0;
    mat[11] = 0.0;
    mat[15] = 1.0;
}

void Object::multMatrix(matrix mat, matrix buffer)
{
  this->mat = matrixXmatrix(buffer, this->mat, mat);
}
