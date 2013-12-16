#ifndef __WEREWOLF_H__
#define __WEREWOLF_H__
#include <string>
#include "enemy.h"

class Werewolf : public Enemy {
public:
  Werewolf();
  virtual char getID();
  virtual std::string getName();
};

#endif
