#ifndef TRIMESH_H
#define TRIMESH_H

#define TRIMESHBUFFER 100

#include "object.h"
#include "geo3d/geo3d.h"

class TriMesh : public Object
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
    void draw();
};

#endif
