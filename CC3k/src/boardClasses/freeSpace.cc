#include "cell.h"
#include "freeSpace.h"
#include "../things/character/pc/pc.h"
#include "../things/item/gold/gold.h"
using namespace std;

FreeSpace::FreeSpace(): th(NULL) {}

FreeSpace::FreeSpace(Thing* th):th(th) {}

FreeSpace::~FreeSpace() { delete removeOccupant(); }

bool FreeSpace::isFreeSpace() { return true; }

bool FreeSpace::occupied() { return (th!=NULL); }

Thing* FreeSpace::removeOccupant() { 
  Thing* tmp = th;
  th = NULL;
  return tmp;
}

void FreeSpace::addOccupant(Thing* t) {
  th = t;
}

bool FreeSpace::containsStairs() { 
  if (occupied()) return th->isStairs();
  else return false;
}

bool FreeSpace::move(Cell*& c, TextDisplay*& td) {
  if (c->occupied()) {
    Thing* o = c->removeOccupant();
    //if (c->isTile() && o->isGold() && th->isPlayer()) {
    if (c->isTile() && o->canPickUp() && th->isPlayer()) {
      Gold* g = static_cast<Gold*>(o);
      (static_cast<PC*>(th))->collectGold(g);
      delete o;
    }
    /*else if(c->isTile() && o->isPotion() && th->isPlayer()) {
      Potion *p = static_cast<Potion*>(o);
      (static_cast<PC*>(th))->drinkPotion(p);
      delete o;
    }*/
    else {
      c->addOccupant(o);
      return false;
    }
  }

  c->addOccupant(th);
  c->notifyDisplay(*td);
  th = NULL;
  notifyDisplay(*td);

  return true;
}

