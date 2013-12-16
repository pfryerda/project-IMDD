#ifndef __MERCHANT_H__
#define __MERCHANT_H__
#include <string>
#include "enemy.h"

class Merchant : public Enemy {
  bool hasThePlayerHurtMyFriends;
public:
  Merchant();
  Merchant(bool);
  virtual char getID();
  virtual std::string getName();
  virtual bool isHostile();
  virtual bool isMerchant();
  void makeHostile();
};

#endif
