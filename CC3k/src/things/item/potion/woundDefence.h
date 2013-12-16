#ifndef __WOUNDDEFENCE_H__
#define __WOUNDDEFENCE_H__
#include "potion.h"
#include <string>

class WoundDefence : public Potion {
public:
  virtual PC* applyEffect(PC*);
  virtual std::string getName();
  virtual Potion* makePositive();
};

#endif
