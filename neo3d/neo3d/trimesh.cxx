#include "trimesh.h"
#include <stdlib.h>

TriMesh::TriMesh() : Object()
{
    vertexes = (vertex *)malloc(sizeof(vertex) * TRIMESHBUFFER);
    color = (vertex *)malloc(sizeof(vertex) * TRIMESHBUFFER);
    for (int i = 0; i < TRIMESHBUFFER; i++) {
        vertexes[i] = newVertex();
        color[i] = newVertex();
    }
    max_vertexes = TRIMESHBUFFER;
    len = 0;
}

TriMesh::~TriMesh()
{
    delete(vertexes);
    delete(color);
}

void TriMesh::addTriangle(vertex col1, vertex v1,
                          vertex col2, vertex v2,
                          vertex col3, vertex v3)
{
    if (len > (max_vertexes - 4)) {
        max_vertexes += TRIMESHBUFFER;
        vertexes = (vertex *)realloc(vertexes, sizeof(vertex) * max_vertexes);
        color = (vertex *) realloc(color, sizeof(vertex) * max_vertexes);
        for (int i = len; i < max_vertexes; i++) {
            vertexes[i] = newVertex();
            color[i] = newVertex();
        }
    }
    color[len][0] = col1[0];
    color[len][1] = col1[1];
    color[len][2] = col1[2];
    vertexes[len][0] = v1[0];
    vertexes[len][1] = v1[1];
    vertexes[len][2] = v1[2];
    len++;

    color[len][0] = col2[0];
    color[len][1] = col2[1];
    color[len][2] = col2[2];
    vertexes[len][0] = v2[0];
    vertexes[len][1] = v2[1];
    vertexes[len][2] = v2[2];
    len++;

    color[len][0] = col3[0];
    color[len][1] = col3[1];
    color[len][2] = col3[2];
    vertexes[len][0] = v3[0];
    vertexes[len][1] = v3[1];
    vertexes[len][2] = v3[2];
    len++;
}

void TriMesh::draw()
{
    glPushMatrix();
    glMultMatrixd(mat);
    glBegin(GL_TRIANGLES);
        for (int i = 0; i < len; i++) {
            glColor3f(color[i][0], color[i][1], color[i][2]);
            glVertex3f(vertexes[i][0], vertexes[i][1], vertexes[i][2]);
        }
    glEnd();
    glPopMatrix();
}
