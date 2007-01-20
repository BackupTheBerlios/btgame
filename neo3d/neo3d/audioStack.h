#ifndef TEXTURESTACK_H
#define TEXTURESTACK_H

typedef struct 
{
  char *filename;
  unsigned int alIndex;
} AudioRelation;

class AudioStack
{
 private:
  //char **fileList;
  AudioRelation *fileList;
  char *path;
  int count;

 public:
  AudioStack();

  void setPath(char *path);
  int addAudio(char *filename);
};

extern AudioStack *audioStack;

#endif /* TEXTURESTACK_H */
