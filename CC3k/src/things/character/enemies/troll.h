#ifndef __TROLL_H__
#define __TROLL_H__
#include <string>
#include "enemy.h"

class Troll : public Enemy {
public:
  Troll();
  virtual char getID();
  virtual std::string getName();
};

#endif
