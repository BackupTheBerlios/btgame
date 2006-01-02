#include "n3dloader.h"
#include <strings.h>
#include "geo3d/geo3d.h"
#include "textureStack.h"
#include "nullmesh.h"


TriMeshTexture *loadTextured(FILE *file)
{
  TriMeshTexture *obj = new TriMeshTexture();
  vertex ver1, ver2, ver3;
  vertex tex1, tex2, tex3;
  char texFile[255];
  ver1 = newVertex();
  ver2 = newVertex();
  ver3 = newVertex();
  tex1 = newVertex();
  tex2 = newVertex();
  tex3 = newVertex();

  
  while (fscanf(file, "%lf %lf %lf %lf %lf %s %lf %lf %lf %lf %lf %s %lf %lf %lf %lf %lf %s",
		&ver1[0], &ver1[1], &ver1[2],
		&tex1[0], &tex1[1], texFile,
		&ver2[0], &ver2[1], &ver2[2],
		&tex2[0], &tex2[1], texFile,
		&ver3[0], &ver3[1], &ver3[2],
		&tex3[0], &tex3[1], texFile) != EOF) {
    
    obj->addTriangle(tex1, ver1,
		     tex2, ver2,
		     tex3, ver3, texStack->addTexture(texFile));
  } 
  return obj;
}

TriMesh *loadVColored(FILE *file)
{
  TriMesh *obj = new TriMesh();

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
  return obj;
}


DrawObject *N3DLoader::load(char *filename)
{
  FILE *file;
  char buffer[255];
  bool vColor = false;
  bool textured = false;

  /* Try to open file */
  file = fopen(filename, "r");
  if (file == NULL) {
    fprintf(stderr, "Cannot open file: %s\n", filename);
    return new NullMesh();
  }
  
  /* Testing if it is a neo3d object */
  fscanf(file, "%s ", buffer);
  if (strcmp(buffer, "Neo3d")) {
    fprintf(stderr, "%s is not a neo3d object\n", filename);
    return new NullMesh();
  }

  /* Check type */
  fscanf(file, "%s ", buffer);
  if (strcmp(buffer, "Triangle-Object")) {
    fprintf(stderr, "Neo3d Object %s has an unknown type\n", filename);
    return new NullMesh();
  }

  /* Version check */
  fscanf(file, "%s ", buffer);
  if (!(!strcmp(buffer, "0.0.1") || !strcmp(buffer, "0.0.2"))) {
    fprintf(stderr, "%s has an unknown version: %s\n", filename, buffer);
    return new NullMesh();
  }

  /* Getting flags */
  while (fgets(buffer, 255, file)) {
    if (!strcmp (buffer, "vColors\n"))
      vColor = true;
    else if (!strcmp (buffer, "Textured\n"))
      textured = true;
    else if(!strcmp (buffer, "RawData\n")) 
      break;
    else
      fprintf(stderr, "Warning: Unknown flag in %s: %s", filename, buffer);
  }

  /* Choose load function */
  if (vColor && !textured)
    return loadVColored(file);
  else if (!vColor && textured)
    return loadTextured(file);
  else {
    fprintf(stderr, "OOOps! A little bug in neo3d engine. Sorry, cannot load %s", filename);
    return new NullMesh();
  }
}

