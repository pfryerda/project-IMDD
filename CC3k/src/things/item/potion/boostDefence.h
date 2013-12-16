#ifndef __BOOSTDEFENCE_H__
#define __BOOSTDEFENCE_H__
#include "potion.h"
#include <string>

class BoostDefence : public Potion {
public:
  virtual PC* applyEffect(PC*);
  virtual std::string getName();
};

#endif
