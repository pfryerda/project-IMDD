#include <iostream>
#include <unistd.h>
#include <pwd.h>
#include <vector>
#include <stdlib.h>
#include "cell.h"
#include "../things/character/pc/pc.h"

class Thing;

using namespace std;

//ctor and dtor
Cell::Cell():coords(make_pair(-1, -1)), playerNearBy(false) {}
Cell::~Cell() {}

//Geters functions
int  Cell::r()              const { return coords.first;  }
int  Cell::c()              const { return coords.second; }
bool Cell::isPlayerNearBy() const { return playerNearBy;  }

//Used for dragonHoard to check if it can spawn here and enemies to see if they can move
int Cell::numAvaliableNeighbours() {
  int count = 0;
  for (vector<Cell*>::iterator i = neighbours.begin(); i != neighbours.end(); ++i) {
    if ((*i)->isTile() && !((*i)->occupied())) ++count;
  }
  return count;
}

//Used for deagonHoard to find where to put its dragon and enemies to find where to move
Cell* Cell::getRandNeighbour() {
  Cell* retCell = NULL;
  while (true) {
    int randNum = rand() % neighbours.size();
    retCell = neighbours[randNum];
    if (!(retCell->occupied()) && retCell->isTile()) return retCell;
  }
}

//Used to make action msg
string Cell::getNeighbourNames() {
  vector<string> names;
  for (unsigned int i = 0; i < neighbours.size(); ++i) {
    if (neighbours[i]->occupied() && neighbours[i]->isTile()) {
       Thing *th = neighbours[i]->removeOccupant();
       if (th->isGold()) names.push_back(th->getName());
       else if (th->isPotion()) {
         PC* player = static_cast<PC*>(removeOccupant());
         if (player->getDiscoveredPotion(th->getName()))  names.push_back(th->getName());
         else                                             names.push_back("unknown potion");
         addOccupant(player);
       }
       neighbours[i]->addOccupant(th);
    }
  }
  
  string actionMsg = "";
  if (names.size() > 0) {
    actionMsg += " and sees";
    for (unsigned int i = 0; i < names.size(); ++i) {
       if (names[i][0] == 'a' || names[i][0] == 'e' || names[i][0] == 'o' || names[i][0] == 'i' || names[i][0] == 'u') actionMsg += " an ";
       else actionMsg += " a ";
       actionMsg += names[i];
       if (i+1 != names.size())  actionMsg += "," ;
       if (i+2 == names.size())  actionMsg += " and";
     }
   }

  return actionMsg;
}

//Observer pattern functions
void Cell::setCoords(const int& r, const int& c) { coords.first = r, coords.second = c; }
void Cell::addNeighbour(Cell* neighbour)         { neighbours.push_back(neighbour);     }
void Cell::notify()                              { playerNearBy = !playerNearBy;    }
void Cell::notifyNeighbours() { for (vector<Cell*>::iterator i = neighbours.begin(); i != neighbours.end(); ++i) (*i)->notify(); }

//Used for finding neghibour of Player for moving,attack,and drinking
pair<Cell*, string> Cell::getNeighbour(string dir, string actionMsg) {
  Cell* newCell = NULL;
  if      (dir == "ne" || dir == "northeast" || dir == "9") newCell = neighbours[2], actionMsg += "North East";
  else if (dir == "no" || dir == "north"     || dir == "8") newCell = neighbours[1], actionMsg += "North";
  else if (dir == "nw" || dir == "northwest" || dir == "7") newCell = neighbours[0], actionMsg += "North West";
  else if (dir == "ea" || dir == "east"      || dir == "6") newCell = neighbours[4], actionMsg += "East";
  else if (dir == "we" || dir == "west"      || dir == "4") newCell = neighbours[3], actionMsg += "West";
  else if (dir == "se" || dir == "southeast" || dir == "3") newCell = neighbours[7], actionMsg += "South East";
  else if (dir == "so" || dir == "south"     || dir == "2") newCell = neighbours[6], actionMsg += "South";
  else if (dir == "sw" || dir == "southwest" || dir == "1") newCell = neighbours[5], actionMsg += "South West";
  else if (dir == "hello" || dir == "Hello") actionMsg = dir + " " + (getpwuid(getuid()))->pw_name;
  else                                actionMsg = "Invalid command: use no,so,ea,we,ne,nw,se,sw to move the player";
  return make_pair(newCell, actionMsg);
}

//virtual functions
bool Cell::isTile()                         { return false; }
bool Cell::isFreeSpace()                    { return false; }
bool Cell::occupied()                       { return true; }
Thing* Cell::removeOccupant()               { return NULL; }
void Cell::addOccupant(Thing* t)            {}
bool Cell::move(Cell*& c, TextDisplay*& td) { return false; }
bool Cell::containsStairs()                 { return false; }

//Used in attaching gold with dragons
bool Cell::isNeighbour(Cell*& other) const { return ((this->r()-1) <= other->r() && other->r() <= (this->r()+1) && (this->c()-1) <= other->c() && other->c() <= (this->c()+1)); }

//Used in Cell sorting
bool Cell::operator<(const Cell*& other) { return (((this->r() != other->r()) || (this->c() < other->c())) && ((this->r() == other->r()) ||  this->r() < other->r())); }
