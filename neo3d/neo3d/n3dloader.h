#ifndef N3DLOADER_H
#define N3DLOADER_H

#include "stdio.h"
#include "trimesh.h"

class N3DLoader
{
 public:
    static TriMesh *loadFile(char *filename);
    static TriMesh *loadFile(FILE *file);

    static TriMesh *loadTriangleObject(FILE *file);
};

#endif // N3DLOADER_H
