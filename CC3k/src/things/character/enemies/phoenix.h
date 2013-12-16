#ifndef __PHOENIX_H__
#define __PHOENIX_H__
#include <string>
#include "enemy.h"

class Phoenix : public Enemy {
public:
  Phoenix();
  virtual char getID();
  virtual std::string getName();
};

#endif
