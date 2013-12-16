#ifndef __WOUNDATTACK_H__
#define __WOUNDATTACK_H__
#include "potion.h"
#include <string>

class WoundAttack : public Potion {
public:
  virtual PC* applyEffect(PC*);
  virtual std::string getName();
  virtual Potion* makePositive();
};

#endif
