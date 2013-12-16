#ifndef __WADECORATOR_H__
#define __WADECORATOR_H__
#include "decorator.h"

class PC;

class waDecorator : public Decorator {
public:
  waDecorator(PC*);
  virtual unsigned int getAtk() const;
};

#endif
