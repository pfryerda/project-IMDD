#ifndef __BOOSTATTACK_H__
#define __BOOSTATTACK_H__
#include "potion.h"
#include <string>

class BoostAttack : public Potion {
public:
  virtual PC* applyEffect(PC*);
  virtual std::string getName();
};

#endif
