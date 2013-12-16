#ifndef __DRAGON_H__
#define __DRAGON_H__
#include <string>
#include "enemy.h"

class Cell;

class Dragon : public Enemy {
  Cell* goldCell;
public:
  Dragon();
  Dragon(Cell*);
  virtual char getID();
  virtual std::string getName();
  virtual bool canMove();
  virtual bool isHostile();
  virtual bool isDragon();
  void notifyGold();
  void addGold(Cell*);
};

#endif
