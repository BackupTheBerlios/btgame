#ifndef TEXTURESTACK_H
#define TEXTURESTACK_H

typedef struct 
{
  char *filename;
  unsigned int glIndex;
} TextureRelation;

class TextureStack
{
 private:
  //char **fileList;
  TextureRelation *fileList;
  char *path;
  int count;

 public:
  TextureStack();

  void setPath(char *path);
  int addTexture(char *filename);
};

extern TextureStack *texStack;

#endif /* TEXTURESTACK_H */
