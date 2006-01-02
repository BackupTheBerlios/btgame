#ifndef N3DLOADER_H
#define N3DLOADER_H

#include <stdio.h>
#include "trimesh.h"
#include "trimeshTexture.h"
#include "drawobject.h"

class N3DLoader
{
 public:
    static DrawObject *load(char *filename);
};

#endif // N3DLOADER_H
