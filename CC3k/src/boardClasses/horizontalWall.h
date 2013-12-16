#ifndef __HORIZONTALWALL_H__
#define __HORIZONTALWALL_H__

class TextDisplay;
class Cell;

class HorizontalWall : public Cell {
public:
  virtual void notifyDisplay(TextDisplay&);
};

#endif
