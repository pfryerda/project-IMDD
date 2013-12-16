#ifndef __GAME_H___
#define __GAME_H__
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include "things/stair.h"

class Floor;
class Cell;
class PC;

const unsigned int NUMLEVELS  =  8;
const unsigned int NUMSTAIRS  =  1;
const unsigned int NUMGOLD    = 10;
const unsigned int NUMPOTIONS = 10;
const unsigned int NUMENEMIES = 20;

class Game {
  static Game* instance;

  bool gameRunning;
  unsigned int currLevelNum;
  Floor* currLevel;
  Stairs* stairs;
  Cell* PlayerCell;
  std::set<Cell*> enemies;
  bool hostileMerchants;

  bool tHelp;
  bool tLegend;
  bool firstTime;

public:
  static Game* getInstance(std::fstream*);
  ~Game();

  bool done() const;

  void restart();
  void playerMove(std::string);
  void playerAttack(std::string);
  void playerDrink(std::string);
  void toggleHelp();
  void toggleLegend();
  std::ostream& gamePrint(std::ostream& out)     const;
  std::ostream& displayHelp(std::ostream& out)   const;
  std::ostream& displayLegend(std::ostream& out) const;
  void clearScreen()   const;
  friend std::ostream& operator<<(std::ostream&, const Game&);

  void addEnemy(Cell*);
  void setPlayerCell(Cell*);
  void setStairs(Stairs*);

private:
  Game(std::fstream*);
  static void CleanUp(void);

  std::string stepEnemy();
  void notifyMerchants();

  void buildGame(int, PC*);
  PC * buildPlayer();
  void gameOver(bool);
  void nextLevel();
};

#endif
