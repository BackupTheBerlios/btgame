#include "textureStack.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_opengl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 100

TextureStack *texStack;

TextureStack::TextureStack()
{
  fileList = (TextureRelation *) malloc(sizeof(TextureRelation) * BUFFER_SIZE);
  path = NULL;
  count = 0;
}

void TextureStack::setPath(char *path)
{
  free(this->path);
  this->path = (char *) malloc(sizeof(char) * strlen(path));
  this->path = strcpy(this->path, path);
}

int TextureStack::addTexture(char *filename)
{
  char *completeFilename;
  GLuint glTexIndex;
  GLenum glError;

  for (int i = 0; i < count; i++)
    if (!strcmp(fileList[i].filename, filename))
      return fileList[i].glIndex;

  //  char *completeFilename = new char[strlen(path) + strlen(filename) + 10];
  completeFilename = (char *) malloc(sizeof(char) * (strlen(path) + strlen(filename) + 2));
  sprintf(completeFilename, "%s/%s", path, filename);
  SDL_Surface *image = IMG_Load(completeFilename);
  if (image == NULL) {
    fprintf(stderr, "Image not found\n" );
    return -1;
  }
  SDL_DisplayFormat(image);

  glEnable(GL_TEXTURE_2D);
  glGenTextures(1, &glTexIndex);
  glBindTexture(GL_TEXTURE_2D, glTexIndex);
  glError = glGetError();
  switch (glError) {
  case GL_INVALID_ENUM:
    printf("Invalid enum\n");
    break;
  case GL_INVALID_OPERATION:
    printf("Invalid operation\n");
    break;
    } 
    
  //glTexImage2D(GL_TEXTURE_2D, 0, 3, image->w, image->h, 0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
  gluBuild2DMipmaps(GL_TEXTURE_2D, 3, image->w, image->h, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
  //  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); 
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glDisable(GL_TEXTURE_2D);
  //  printf("%s %i\n", completeFilename, glTexIndex);
  
  this->fileList[count].filename = (char *) malloc(sizeof(char) * (strlen(filename) + 10));
  this->fileList[count].filename = strcpy(this->fileList[count].filename, filename);
  this->fileList[count].glIndex = glTexIndex; 
  count++;
  return glTexIndex;
}
