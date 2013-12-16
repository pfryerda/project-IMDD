#ifndef __TILE_H__
#define __TILE_H__

class TextDisplay;
class Cell;
class FreeSpace;

class Tile : public FreeSpace {
public:
  Tile();
  Tile(Thing*);
  virtual bool isTile();
  virtual void notifyDisplay(TextDisplay& td);
};

#endif
