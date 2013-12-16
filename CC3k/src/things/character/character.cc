#include <iostream>
#include <math.h>
#include "character.h"
using namespace std;

Character::Character(unsigned int HP, unsigned int Atk, unsigned int Def): HP(HP), Atk(Atk), Def(Def) {}

Character::~Character() {}

void Character::setHP(unsigned int hp) { HP = hp; }
unsigned int Character::getHP()  const { return HP;  }
unsigned int Character::getAtk() const { return Atk; }
unsigned int Character::getDef() const { return Def; }
int Character::strike(Character* e) {
  return (e->damage(getAtk()));
}

int Character::damage(int a) { 
   int dmg = ceil((static_cast<float>(100)/(100+getDef()))*a);
   int newHp = getHP() - dmg;
   if (newHp < 0) setHP(0);
   else           setHP(newHp);
   return dmg;
}

bool Character::isDead() { return getHP()==0; }

ostream& operator<<(ostream& out, const Character& c) {
  out << "HP: "  << c.getHP() << endl;
  out << "Atk: " << c.getAtk() << endl;
  return out << "Def: " << c.getDef();
}
