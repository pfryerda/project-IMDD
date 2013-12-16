#include <string>
#include "../../../boardClasses/cell.h"
#include "../../item/gold/dragonHoard.h"
#include "dragon.h"
using namespace std;

Dragon::Dragon():Enemy(150, 20, 20), goldCell(NULL) {}
Dragon::Dragon(Cell* g):Enemy(150, 20, 20), goldCell(g) {}
char Dragon::getID()      { return 'D'; }
string Dragon::getName()  { return "Dragon"; }
bool Dragon::canMove()    { return false; }
bool Dragon::isHostile()  { return goldCell->isPlayerNearBy(); }
bool Dragon::isDragon()   { return true; }
void Dragon::notifyGold() { 
  DragonHoard* g = static_cast<DragonHoard*>(goldCell->removeOccupant());
  g->notify();
  goldCell->addOccupant(g);
}
void Dragon::addGold(Cell* g) { goldCell = g; }
