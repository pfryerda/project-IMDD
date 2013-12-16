#ifndef __GOLD_H__
#define __GOLD_H__
#include "../item.h"
#include "../../thing.h"

class Gold : public Item {
public:
  virtual int getAmount();
  char getID();
  virtual std::string getName();
  virtual bool canPickUp();
  virtual bool isGold();
};

#endif
