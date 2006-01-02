#ifndef TRIMESHTEXTURE_H
#define TRIMESHTEXTURE_H

#define TRIMESHBUFFER 100

#include "drawobject.h"
#include "geo3d/geo3d.h"

class TriMeshTexture : public DrawObject
{
 private:
    vertex *vertexes;
    vertex *texPos;
    int *textures;
    int max_vertexes;
    int len;
 public:
    TriMeshTexture();
    ~TriMeshTexture();

    void addTriangle(vertex texPos1, vertex v1, 
                     vertex texPos2, vertex v2, 
                     vertex texPos3, vertex v3, 
		     int texture);
    void draw();
};

#endif
