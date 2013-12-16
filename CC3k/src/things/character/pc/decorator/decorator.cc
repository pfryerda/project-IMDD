#include "decorator.h"
using namespace std;

Decorator::Decorator(PC* pc):PC(0, 0, 0), pc(pc) {}
Decorator::~Decorator() { delete pc; }

PC* Decorator::removePotionEffects() {
  PC* oldPlayer = pc->removePotionEffects();
  pc = NULL;
  delete this;
  return oldPlayer;
}

void Decorator::makePotionDiscovered(string s)  { pc->makePotionDiscovered(s); }
bool Decorator::isElf()                         { return pc->isElf(); }
string Decorator::getName()                     { return pc->getName(); }
bool Decorator::getDiscoveredPotion(string str) { return pc->getDiscoveredPotion(str); }
void Decorator::collectGold(Gold *&g)           { pc->collectGold(g); }
void Decorator::setChamberNum(int n)            { pc->setChamberNum(n); }
int Decorator::getChamberNum()                  { return pc->getChamberNum(); }
unsigned int Decorator::getCurrScore()          { return pc->getCurrScore(); }
unsigned int Decorator::getFinalScore()         { return pc->getFinalScore(); }
unsigned int Decorator::getAtk()          const { return pc->getAtk(); }
unsigned int Decorator::getDef()          const { return pc->getDef(); }
unsigned int Decorator::getHP()           const { return pc->getHP(); }
unsigned int Decorator::getMaxHP()        const { return pc->getMaxHP(); }
void Decorator::setHP(unsigned int n)           { pc->setHP(n); }
