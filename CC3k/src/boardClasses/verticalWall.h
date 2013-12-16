#ifndef __VERTICALWALL_H__
#define __VERTICALWALL_H__

class TextDisplay;
class Cell;

class VerticalWall : public Cell {
public:
  virtual void notifyDisplay(TextDisplay&);
};

#endif
