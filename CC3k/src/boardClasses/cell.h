#ifndef __CELL_H__
#define __CELL_H__
#include <string>
#include <vector>

class TextDisplay;
class Thing;

class Cell {
  std::vector<Cell*> neighbours;
  std::pair<int, int> coords;
  bool playerNearBy;

public:
  Cell();
  virtual ~Cell() = 0;

  int r() const;
  int c() const;
  int numAvaliableNeighbours();
  std::string getNeighbourNames();
  virtual bool isTile();
  virtual bool isFreeSpace();
  virtual bool occupied();
  bool isPlayerNearBy() const;
  virtual bool containsStairs();

  virtual Thing* removeOccupant();
  virtual void addOccupant(Thing*);
  virtual bool move(Cell*&, TextDisplay*&);
  Cell* getRandNeighbour();

  void setCoords(const int&, const int&);
  void addNeighbour(Cell* neighbour);
  void notify();
  void notifyNeighbours();
  virtual void notifyDisplay(TextDisplay&) = 0;

  std::pair<Cell*, std::string> getNeighbour(std::string, std::string);

  bool isNeighbour(Cell*& other) const;
  bool operator<(const Cell*&);
};

#endif
