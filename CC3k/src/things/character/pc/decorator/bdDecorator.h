#ifndef __BDDECORATOR_H__
#define __BDDECORATOR_H__
#include "decorator.h"

class PC;

class bdDecorator : public Decorator {
public:
  bdDecorator(PC*);
  virtual unsigned int getDef() const;
};

#endif
