#include "n3dloader.h"
#include <strings.h>
#include "geo3d/geo3d.h"

TriMesh *N3DLoader::loadFile(char *filename)
{
    return loadFile(fopen(filename, "r"));
}

TriMesh *N3DLoader::loadFile(FILE *file)
{
    TriMesh *obj = new TriMesh();
    char buffer[255];
    /* Checking if it is neo3d file */
    
    fscanf(file, "%s ", buffer);
    if (strcmp(buffer, "Neo3d"))
        return NULL;

    /* Checking type */

    fscanf(file, "%s\n", buffer);
    if (!strcmp(buffer, "Triangle-Object")) {
        return loadTriangleObject(file);
    }
    else {
        return NULL;
    }
}

TriMesh *N3DLoader::loadTriangleObject(FILE *file)
{
    TriMesh *obj = new TriMesh();
    bool hasColor = false;
    char buffer[255];
    /* Checking version */
    fscanf(file, "%s", buffer);
    if (!strcmp(buffer, "0.0.1")) {
        /* Checking header */
        while (fgets(buffer, 255, file)) {
            if (!strcmp (buffer, "vColors\n"))
                hasColor = true;
            else if(!strcmp (buffer, "RawData\n")) 
                break;
        }

        /* Reading raw data */
        if (hasColor) {
            vertex ver1, ver2, ver3;
            vertex col1, col2, col3;
            ver1 = newVertex();
            ver2 = newVertex();
            ver3 = newVertex();
            col1 = newVertex();
            col2 = newVertex();
            col3 = newVertex();
            
            while (fscanf(file, "%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf ",
                          &ver1[0], &ver1[1], &ver1[2],
                          &col1[0], &col1[1], &col1[2],
                          &ver2[0], &ver2[1], &ver2[2],
                          &col2[0], &col2[1], &col2[2],
                          &ver3[0], &ver3[1], &ver3[2],
                          &col3[0], &col3[1], &col3[2]) != EOF) {


                obj->addTriangle(col1, ver1,
                                 col2, ver2,
                                 col3, ver3);
            }
        }
        else 
            return NULL;
    }
    return obj;
}
