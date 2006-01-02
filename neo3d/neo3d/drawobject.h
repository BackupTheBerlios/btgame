#ifndef DRAWOBJECT_H
#define DRAWOBJECT_H

#include "object.h"

class DrawObject : public Object /* abstract */
{
 public:
  virtual void draw() = 0;
};

#endif /* DRAWOBJECT_H */
