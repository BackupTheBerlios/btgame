#ifndef TRIMESH_H
#define TRIMESH_H

#define TRIMESHBUFFER 100

#include "drawobject.h"
#include "geo3d/geo3d.h"

class TriMesh : public DrawObject
{
 private:
    vertex *vertexes;
    vertex *color;
    int max_vertexes;
    int len;
 public:
    TriMesh();
    ~TriMesh();

    void addTriangle(vertex col1, vertex v1,
                     vertex col2, vertex v2,
                     vertex col3, vertex v3);
    virtual void draw();
};

#endif
