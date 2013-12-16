#ifndef __THING_H__
#define __THING_H__
#include <string>

class Thing {
public:
  virtual ~Thing() = 0;

  virtual char getID() = 0;
  virtual std::string getName() = 0;
  virtual bool canPickUp();
  virtual bool isGold();
  virtual bool isPotion();
  virtual bool isPlayer();
  virtual bool isEnemy();
  virtual bool isMerchant();
  virtual bool isDragon();
  virtual bool isStairs();
};

#endif
