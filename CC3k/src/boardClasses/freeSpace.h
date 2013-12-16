#ifndef __FREESPACE_H__
#define __FREESPACE_H__

class TextDisplay;
class Cell;
class Thing;

class FreeSpace : public Cell {
protected:
  Thing* th;
public:
  FreeSpace();
  FreeSpace(Thing*);
  ~FreeSpace();
  virtual bool isFreeSpace();
  virtual bool occupied();
  virtual Thing* removeOccupant();
  virtual void addOccupant(Thing*);
  virtual bool containsStairs();
  virtual bool move(Cell*&, TextDisplay*&);
  virtual void notifyDisplay(TextDisplay&) = 0;
};

#endif
