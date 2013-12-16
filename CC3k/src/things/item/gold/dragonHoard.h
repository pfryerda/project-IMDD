#ifndef __DRAGONHOARD_H__
#define __DRAGONHOARD_H__
#include "gold.h"

class DragonHoard : public Gold {
  bool isMyDaddyDead;
public:
  DragonHoard();
  virtual std::string getName();
  virtual int getAmount();
  virtual bool canPickUp();
  void notify();
};

#endif
