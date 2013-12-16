#ifndef __ENEMY_H__
#define __ENEMY_H__
#include "../character.h"

class Enemy : public Character {
public:
  Enemy(unsigned int, unsigned int, unsigned int);
  virtual ~Enemy() = 0;
  virtual bool canMove();
  virtual bool isHostile();
  virtual bool isEnemy();
};

#endif
