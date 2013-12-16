#ifndef __GOBLIN_H__
#define __GOLBIN_H__
#include <string>
#include "enemy.h"

class Goblin : public Enemy {
public:
  Goblin();
  virtual char getID();
  virtual std::string getName();
};

#endif
