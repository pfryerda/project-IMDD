#ifndef __FLOOR_H__
#define __FLOOR_H__
#include <iostream>
#include <fstream>
#include <vector>
#include <set>

class Game;
class PC;

class TextDisplay;
class Cell;
class Thing;
class Stairs;
class EmptySpace;
class HorizontalWall;
class VerticalWall;

class Floor {
  std::vector< std::vector<Cell*> > theGrid;
  std::vector< std::vector<Cell*> > chambers;
  TextDisplay* td;

  EmptySpace* es;
  HorizontalWall* hw;
  VerticalWall* vw;

  unsigned int numStairsSpawned;
  unsigned int numGoldSpawned;
  unsigned int numPotionsSpawned;
  unsigned int numEnemiesSpawned;

public:
  Floor();
  Floor(std::fstream*, PC*, Game*);
  ~Floor();
  void clearGrid();

  TextDisplay* getDisplay();

  Cell* generatePlayer(PC*&, int);
  std::set<Cell*> generate(std::set<Cell*>, Stairs*, bool, int);

  friend std::ostream& operator<<(std::ostream&, const Floor&);

private:
  Cell* spawn(Thing*, int);
};

#endif
