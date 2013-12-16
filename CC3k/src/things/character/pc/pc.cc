#include "../../thing.h"
#include "../../item/gold/gold.h"
#include <iostream>
#include "pc.h"
using namespace std;

PC::PC(unsigned int HP, unsigned int Atk, unsigned int Def): Character(HP, Atk, Def), MaxHP(HP), chamberNum(5), Money(0) {
  discoveredPotions["RH"] = false;
  discoveredPotions["PH"] = false;
  discoveredPotions["BA"] = false;
  discoveredPotions["BD"] = false;
  discoveredPotions["WD"] = false;
  discoveredPotions["WA"] = false;
}

PC::~PC() {}

unsigned int PC::getMaxHP() const { return MaxHP; }

PC* PC::removePotionEffects() { return this; }

void PC::makePotionDiscovered(string s) { discoveredPotions[s] = true; }

bool PC::getDiscoveredPotion(string s) { return discoveredPotions[s]; }

void PC::collectGold(Gold*& g) { Money += g->getAmount(); }

PC* PC::drinkPotion(Potion *&p) {
  makePotionDiscovered(p->getName());
  if (this->isElf()) {
    Potion* newPotion = p->makePositive();
    PC* newPlayer = newPotion->applyEffect(this);
    if (p != newPotion) delete newPotion;
    return newPlayer;    
  } else {
    return p->applyEffect(this);
  }
}

int PC::strike(Character* e) {
  int dmg = e->damage(getAtk());
  if (e->isDead()) {
    Gold* g = new Gold();
    this->collectGold(g);
    delete g;
  }
  return dmg;
}

void PC::setChamberNum(int n) { chamberNum = n; }
int  PC::getChamberNum()      { return chamberNum; }

char PC::getID()    { return '@'; }
bool PC::isPlayer() { return true; }
bool PC::isElf()    { return false; }

unsigned int PC::getCurrScore()  { return Money; }
unsigned int PC::getFinalScore() { return Money; }
