#include "audioStack.h"
#include <AL/al.h>
#include <AL/alut.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 100

AudioStack *texStack;

AudioStack::AudioStack()
{
  fileList = (AudioRelation *) malloc(sizeof(AudioRelation) * BUFFER_SIZE);
  path = NULL;
  count = 0;
}

void AudioStack::setPath(char *path)
{
  free(this->path);
  this->path = (char *) malloc(sizeof(char) * strlen(path));
  this->path = strcpy(this->path, path);
}

int AudioStack::addAudio(char *filename)
{
  char *completeFilename;

  for (int i = 0; i < count; i++)
    if (!strcmp(fileList[i].filename, filename))
      return fileList[i].alIndex;

  //  char *completeFilename = new char[strlen(path) + strlen(filename) + 10];
  completeFilename = (char *) malloc(sizeof(char) * (strlen(path) + strlen(filename) + 2));
  sprintf(completeFilename, "%s/%s", path, filename);


  alGenBuffers(1, &fileList[count].alIndex);
  if (alGetError() != AL_NO_ERROR)
    return AL_FALSE;

  ALenum format;
  ALsizei size;
  ALvoid *data;
  ALsizei freq;

  alutLoadWAVFile(completeFilename, &format, &data, &size, &freq, AL_FALSE);
  alBufferData(fileList[count].alIndex, format, data, size, freq);
  alutUnloadWAV(format, data, size, freq);

  this->fileList[count].filename = (char *) malloc(sizeof(char) * (strlen(filename) + 10));
  this->fileList[count].filename = strcpy(this->fileList[count].filename, filename);
  count++;
  return fileList[count-1].alIndex;
}
