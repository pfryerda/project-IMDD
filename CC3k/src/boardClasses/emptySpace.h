#ifndef __EMPTYSPACE_H__
#define __EMPTYSPACE_H__

class TextDisplay;
class Cell;

class EmptySpace : public Cell {
public:
  virtual void notifyDisplay(TextDisplay&);
};

#endif
