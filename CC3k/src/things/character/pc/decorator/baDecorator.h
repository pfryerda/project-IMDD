#ifndef __BADECORATOR_H__
#define __BADECORATOR_H__
#include "decorator.h"

class PC;

class baDecorator : public Decorator {
public:
  baDecorator(PC*);
  virtual unsigned int getAtk() const;
};

#endif
