#ifndef __VAMPIRE_H__
#define __VAMPIRE_H__
#include <string>
#include "enemy.h"

class Vampire : public Enemy {
public:
  Vampire();
  virtual char getID();
  virtual std::string getName();
};

#endif
