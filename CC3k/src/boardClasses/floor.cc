#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <set>

#include "textDisplay.h"
#include "cell.h"
#include "emptySpace.h"
#include "door.h"
#include "verticalWall.h"
#include "horizontalWall.h"
#include "passage.h"
#include "tile.h"
#include "floor.h"

#include "../game.h"
#include "../things/stair.h"
#include "../things/character/pc/pc.h"
#include "../things/character/enemies/vampire.h"
#include "../things/character/enemies/werewolf.h"
#include "../things/character/enemies/troll.h"
#include "../things/character/enemies/goblin.h"
#include "../things/character/enemies/phoenix.h"
#include "../things/character/enemies/merchant.h"
#include "../things/character/enemies/dragon.h"
#include "../things/item/gold/smallHoard.h"
#include "../things/item/gold/merchantHoard.h"
#include "../things/item/gold/dragonHoard.h"
#include "../things/item/potion/poisonHealth.h"
#include "../things/item/potion/restoreHealth.h"
#include "../things/item/potion/boostAttack.h"
#include "../things/item/potion/boostDefence.h"
#include "../things/item/potion/woundAttack.h"
#include "../things/item/potion/woundDefence.h"

using namespace std;

class Thing;
class Gold;

//Ctors

Floor::Floor():td(NULL), numStairsSpawned(0), numGoldSpawned(0), numPotionsSpawned(0), numEnemiesSpawned(0) {}

Floor::Floor(fstream* f, PC* p, Game* g):numStairsSpawned(0), numGoldSpawned(0), numPotionsSpawned(0), numEnemiesSpawned(0) {
  td = new TextDisplay();

  es = new EmptySpace();
  hw = new HorizontalWall();
  vw = new VerticalWall();

  vector< pair<Dragon*, Cell*> > dragonCells;
  vector<Cell*> goldCells;

  string line;
  
  //Make grid from file
  for (int i = 0; i < NUMROWS; ++i) {
    vector<Cell*> row;
    getline(*f, line);

    for (int j = 0; j < NUMCOLUMNS; ++j) {
      if      (line[j] == ' ') row.push_back(es);
      else if (line[j] == '+') row.push_back(new Door());
      else if (line[j] == '|') row.push_back(vw);
      else if (line[j] == '-') row.push_back(hw);
      else if (line[j] == '#') row.push_back(new Passage());
      else if (line[j] == '.') row.push_back(new Tile());

      else if (line[j] == '0') row.push_back(new Tile(new RestoreHealth()));
      else if (line[j] == '1') row.push_back(new Tile(new BoostAttack()));
      else if (line[j] == '2') row.push_back(new Tile(new BoostDefence()));
      else if (line[j] == '3') row.push_back(new Tile(new PoisonHealth()));
      else if (line[j] == '4') row.push_back(new Tile(new WoundAttack()));
      else if (line[j] == '5') row.push_back(new Tile(new WoundDefence()));

      else if (line[j] == '6') row.push_back(new Tile(new Gold()));
      else if (line[j] == '7') row.push_back(new Tile(new SmallHoard()));
      else if (line[j] == '8') row.push_back(new Tile(new MerchantHoard()));
      else if (line[j] == '9') {
        row.push_back(new Tile(new DragonHoard()));
        goldCells.push_back(row[j]);
      }

      else if (line[j] == 'V') row.push_back(new Tile(new Vampire()));
      else if (line[j] == 'W') row.push_back(new Tile(new Werewolf()));
      else if (line[j] == 'T') row.push_back(new Tile(new Troll()));
      else if (line[j] == 'N') row.push_back(new Tile(new Goblin()));
      else if (line[j] == 'M') row.push_back(new Tile(new Merchant(false)));
      else if (line[j] == 'X') row.push_back(new Tile(new Phoenix()));
      else if (line[j] == 'D') {
        Dragon* d = new Dragon();
        row.push_back(new Tile(d));
        dragonCells.push_back(make_pair(d, row[j]));
       }

      else if (line[j] == '/') {
        Stairs* s = new Stairs();
        row.push_back(new Tile(s));
        if      ( 3 <= i && i <=  6 &&  3 <= j && j <= 28) s->setChamberNum(0);
        else if (15 <= i && i <= 21 &&  4 <= j && j <= 24) s->setChamberNum(1);
        else if (16 <= i && i <= 21 && 37 <= j && j <= 75) s->setChamberNum(2);
        else if (10 <= i && i <= 12 && 38 <= j && j <= 49) s->setChamberNum(4);
        else                                               s->setChamberNum(3);
        g->setStairs(s);
        ++numStairsSpawned; 
      }
      else if (line[j] == '@') {
        row.push_back(new Tile(p));
        if      ( 3 <= i && i <=  6 &&  3 <= j && j <= 28) p->setChamberNum(0);
        else if (15 <= i && i <= 21 &&  4 <= j && j <= 24) p->setChamberNum(1);
        else if (16 <= i && i <= 21 && 37 <= j && j <= 75) p->setChamberNum(2);
        else if (10 <= i && i <= 12 && 38 <= j && j <= 49) p->setChamberNum(4);
        else                                               p->setChamberNum(3);
        g->setPlayerCell(row[j]); 
      }
      else {
       cerr << "Invalid symbol on map!" << endl;
       cerr << "Expected: +,|,-,#,.,[0-9],space, or certain chars" << endl;
       cerr << "Given: " << line[j] << endl;
      }

      if ('1' <= line[j] && line[j] <= '5') ++numPotionsSpawned;
      if ('6' <= line[j] && line[j] <= '9') ++numGoldSpawned;
      if (isalpha(line[j])) { 
        ++numEnemiesSpawned;
        g->addEnemy(row[j]);
      }

      row[j]->setCoords(i, j);
      row[j]->notifyDisplay(*td);
    }

    theGrid.push_back(row);
  }
  
  //Add Neighbours Cell
  for (unsigned int i = 0; i < theGrid.size(); ++i) {
    for (unsigned int j = 0; j < theGrid[i].size(); ++j) {     
      if (i >= 1 && j >= 1)                                theGrid[i][j]->addNeighbour(theGrid[i-1][j-1]);
      if (i >= 1)                                          theGrid[i][j]->addNeighbour(theGrid[i-1][j]);
      if (j+1 < theGrid[i].size() && i >= 1)               theGrid[i][j]->addNeighbour(theGrid[i-1][j+1]);
      if (j >= 1)                                          theGrid[i][j]->addNeighbour(theGrid[i][j-1]);
      if (j+1 < theGrid[i].size())                         theGrid[i][j]->addNeighbour(theGrid[i][j+1]);
      if (j >= 1 && i+1 < theGrid.size())                  theGrid[i][j]->addNeighbour(theGrid[i+1][j-1]);
      if (i+1 < theGrid.size())                            theGrid[i][j]->addNeighbour(theGrid[i+1][j]);
      if (j+1 < theGrid[i].size() && i+1 < theGrid.size()) theGrid[i][j]->addNeighbour(theGrid[i+1][j+1]);
    }
  }
  
  //Add chambers
  //Chamber 1:
  vector <Cell*> c1;
  for (int i = 3; i < 6; ++i)   for (int j = 3; j < 28; ++j) c1.push_back(theGrid[i][j]);
  chambers.push_back(c1);

  //Chamber 2:
  vector <Cell*> c2;
  for (int i = 15; i < 21; ++i) for (int j = 4; j < 24; ++j) c2.push_back(theGrid[i][j]);
  chambers.push_back(c2);

  //Chamber 3:
  vector <Cell*> c3;
  for (int i = 19; i < 21; ++i) for (int j = 37; j < 75; ++j) c3.push_back(theGrid[i][j]);
  for (int i = 16; i < 18; ++i) for (int j = 65; j < 75; ++j) c3.push_back(theGrid[i][j]);
  chambers.push_back(c3);

  //Chamber 4:
  vector <Cell*> c4;
  for (int i = 3; i < 6; ++i)   for (int j = 39; j < 61; ++j) c4.push_back(theGrid[i][j]);
  for (int i = 7; i < 12; ++i)  for (int j = 61; j < 75; ++j) c4.push_back(theGrid[i][j]);
  for (int i = 5; i < 6; ++i)   for (int j = 62; j < 69; ++j) c4.push_back(theGrid[i][j]);
  c4.push_back(theGrid[6][70]);
  c4.push_back(theGrid[6][71]);
  c4.push_back(theGrid[6][72]);
  chambers.push_back(c4);

  //Chamber 5:
  vector <Cell*> c5;
  for (int i = 10; i < 12; ++i)  for (int j = 38; j < 49; ++j) c5.push_back(theGrid[i][j]);
  chambers.push_back(c5);

  // Conncet CommandLine dragon's with their gold
  for (unsigned int i = 0; i < dragonCells.size();++i) {
    vector<Cell*> possibleMatches;
    int matchNum;
    for (unsigned int j = 0; j < goldCells.size(); ++j) {
      if ((dragonCells[i].second)->isNeighbour(goldCells[j])) {
        possibleMatches.push_back(goldCells[j]);
        matchNum = j;
      }
    }
    if (possibleMatches.size() == 1) {
      (dragonCells[i].first)->addGold(possibleMatches[0]);
      goldCells.erase(goldCells.begin()+matchNum);
      dragonCells.erase(dragonCells.begin()+i);
      i=-1;
    } 
  }
  for (unsigned int i = 0; i < dragonCells.size(); ++i) {
    for (unsigned int j = 0; j < goldCells.size(); ++j) {
       if ((dragonCells[i].second)->isNeighbour(goldCells[j])) {
         (dragonCells[i].first)->addGold(goldCells[j]);
         goldCells.erase(goldCells.begin()+j);
       } 
     }
  }
}


//dtors

Floor::~Floor() {
  delete td;
  td = NULL;

  for (unsigned int i = 0; i < theGrid.size(); ++i) {
    for (unsigned int j = 0; j < theGrid[i].size(); ++j) {
      if (theGrid[i][j]->isFreeSpace()) {
        delete theGrid[i][j];
        theGrid[i][j] = NULL;
      }
    }
  }
  
  delete es;
  delete hw;
  delete vw;
  es = NULL;
  hw = NULL;
  vw = NULL;

}

//Goes through grid and deletes all the things (This includes Player! Remember to take him off the grid before clearing for next level!)
void Floor::clearGrid() {
  numStairsSpawned = 0;
  numGoldSpawned = 0;
  numPotionsSpawned = 0;
  numEnemiesSpawned = 0;
  for (unsigned int i = 0; i < theGrid.size(); ++i) {
    for (unsigned int j = 0; j < theGrid[i].size(); ++j) {
      delete theGrid[i][j]->removeOccupant();
      theGrid[i][j]->notifyDisplay(*td);
    }
  }
}

TextDisplay* Floor::getDisplay() { return td; }


//Generating functions

Cell* Floor::spawn(Thing* th, int pcc = 5) {
  while (true) {
    int numChamber = rand() % 5;
    int spot = rand() % chambers[numChamber].size();
    Cell* retCell = chambers[numChamber][spot];
    if (!retCell->occupied() && numChamber != pcc) {
      retCell->addOccupant(th);
      retCell->notifyDisplay(*td);
      if (th->isPlayer()) static_cast<PC*>(th)->setChamberNum(numChamber);
      if (th->isStairs()) static_cast<Stairs*>(th)->setChamberNum(numChamber);
      return retCell;
    }
  }
}

Cell* Floor::generatePlayer(PC *&pc, int sc = 5) {
  Cell* pCell = this->spawn(pc, sc);
  pCell->notifyNeighbours(); 
  return pCell;
}

set<Cell*> Floor::generate(set<Cell*> enemies, Stairs* s, bool mHostile, int playersChamber) {

  // Generate Stairs
  for (; numStairsSpawned < NUMSTAIRS; ++numStairsSpawned) this->spawn(s, playersChamber);

  // Generate 10 Gold
  for (; numGoldSpawned < NUMGOLD; ++numGoldSpawned) {
    int randNum;
    if (numEnemiesSpawned < NUMENEMIES) randNum = rand() % 8;
    else                                randNum = rand() % 7;

    if      (0 <= randNum && randNum <= 4) this->spawn(new Gold());
    else if (5 <= randNum && randNum <= 6) this->spawn(new SmallHoard());
    else {
      Cell* chosenCell = NULL;
      while (chosenCell == NULL) {
        chosenCell = this->spawn(new DragonHoard());
        if (chosenCell->numAvaliableNeighbours() > 0) break;
        else {
          delete chosenCell->removeOccupant();
          chosenCell->notifyDisplay(*td);
          chosenCell = NULL;
        }
      }
      Cell* dragonCell = chosenCell->getRandNeighbour();
      dragonCell->addOccupant(new Dragon(chosenCell));
      dragonCell->notifyDisplay(*td);
      enemies.insert(dragonCell);
      ++numEnemiesSpawned;
    }
  }

  // Generate 10 Potion
  for (; numPotionsSpawned < NUMPOTIONS; ++numPotionsSpawned) {
    int randNum = rand() % 6;
    if      (randNum == 0) this->spawn(new PoisonHealth());
    else if (randNum == 1) this->spawn(new RestoreHealth());
    else if (randNum == 2) this->spawn(new WoundAttack());
    else if (randNum == 3) this->spawn(new BoostAttack());
    else if (randNum == 4) this->spawn(new WoundDefence());
    else                   this->spawn(new BoostDefence());
  }

  // Generate 10 Enemies
  for (;numEnemiesSpawned < NUMENEMIES; ++numEnemiesSpawned) {
    int randNum = rand() % 18;
    if (0  <= randNum && randNum <= 3 ) enemies.insert(this->spawn(new Werewolf()));
    if (4  <= randNum && randNum <= 6 ) enemies.insert(this->spawn(new Vampire()));
    if (7  <= randNum && randNum <= 11) enemies.insert(this->spawn(new Goblin()));
    if (12 <= randNum && randNum <= 14) enemies.insert(this->spawn(new Troll()));
    if (14 <= randNum && randNum <= 15) enemies.insert(this->spawn(new Phoenix()));
    if (16 <= randNum && randNum <= 17) enemies.insert(this->spawn(new Merchant(mHostile)));
  }
  
  return enemies;
}


ostream& operator<<(ostream& out, const Floor& f) {
  return out << *(f.td);
}
