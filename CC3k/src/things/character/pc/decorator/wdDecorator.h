#ifndef __WDDECORATOR_H__
#define __WDDECORATOR_H__
#include "decorator.h"

class PC;

class wdDecorator : public Decorator {
public:
  wdDecorator(PC*);
  virtual unsigned int getDef() const;
};

#endif
