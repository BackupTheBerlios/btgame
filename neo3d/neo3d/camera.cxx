#include "camera.h"


matrix bmat1, bmat2, bmat3, bmat4;
vertex bver1, bver2, bver3, bver4;

void Camera::init()
{
    bmat1 = newMatrix();
    bmat2 = newMatrix();
    bmat3 = newMatrix();
    bmat4 = newMatrix();
    bver1 = newVertex();
    bver2 = newVertex();
    bver3 = newVertex();
    bver4 = newVertex();
}

void Camera::draw()
{
    glLoadIdentity();
    //    glMultMatrixd(mat);
    gluLookAt(pos[0], pos[1], pos[2],
              front[0] + pos[0], front[1] + pos[1], front[2] + pos[2],
              up[0], up[1], up[2]);
}

void Camera::mouseMotion(int x, int y)
{
    vertex newUp;
    matrix rot;

    rot = createRotMatrix(bmat1, (float) y / 100.0,
                          vertexXvertex(bver1, front,
                                        up));
    matrixXvertex(bver1, rot, front);
    matrixXvertex(bver2, rot, up);
    rot = createRotMatrix(bmat2, (float) x / 100.0, up);
    front = matrixXvertex(front, rot, bver1);

    newUp = bver2;
    bver2 = up;
    up = newUp;

}
