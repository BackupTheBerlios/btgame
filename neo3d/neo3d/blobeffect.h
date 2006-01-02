#ifndef BLOBEFFECT_H
#define BLOBEFFECT_H

#include "drawobject.h"

class BlobEffect : public DrawObject
{
 protected:
  DrawObject *obj;
  vertex axe;
  matrix buffer;
  double speed, length;
 public:
  BlobEffect(DrawObject *obj, vertex axe, double speed, double length);
  ~BlobEffect();
  void draw();
};

#endif /* BLOBEFFECT_H */
