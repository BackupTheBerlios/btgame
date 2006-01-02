#include "blobeffect.h"
#include <math.h>

BlobEffect::BlobEffect(DrawObject *obj, vertex axe, double speed, double length)
{
  this->obj = obj;
  this->axe = axe;
  this->speed = speed;
  this->length = length;
  buffer = newMatrix();
}

BlobEffect::~BlobEffect()
{
  /* Nothing todo */
}

void BlobEffect::draw()
{
  matrix tmp;
  double state = (double) (SDL_GetTicks() % (int)(speed * 10000)) / 1000.0 * (2 * M_PI) / speed;
  createScaleMatrix(buffer, 
		    1.0 + axe[0] * sin(state) * length, 
		    1.0 + axe[1] * sin(state) * length, 
		    1.0 + axe[2] * sin(state) * length);
  tmp = mat;
  mat = buffer;
  buffer = tmp;

  glPushMatrix();
  glMultMatrixd(mat);
  obj->draw();
  glPopMatrix();
}
