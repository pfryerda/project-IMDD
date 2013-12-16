#include "enemy.h"

Enemy::Enemy(unsigned int HP, unsigned int Atk, unsigned int Def):Character(HP, Atk, Def) {}
Enemy::~Enemy() {}
bool Enemy::canMove()   { return true; }
bool Enemy::isHostile() { return true; }
bool Enemy::isEnemy()   { return true; }
