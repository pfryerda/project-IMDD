#ifndef __POISONHEALTH_H__
#define __POISONHEALTH_H__
#include <string>
#include "potion.h"

class PoisonHealth : public Potion {
public:
  virtual PC* applyEffect(PC*);
  virtual std::string getName();
  virtual Potion* makePositive();
};

#endif
