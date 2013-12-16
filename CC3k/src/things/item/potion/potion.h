#ifndef __POTION_H__
#define __POTION_H__

#include <string>
#include "../item.h"
#include "../../thing.h"

class PC;

class Potion : public Item {
public:
  virtual ~Potion() = 0;
  virtual char getID();
  virtual PC* applyEffect(PC*) = 0;
  virtual std::string getName() = 0;
  virtual Potion* makePositive();
  virtual bool isPotion();
};

#endif
