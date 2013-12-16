#ifndef __PASSAGE_H__
#define __PASSAGE_H__

class TextDisplay;
class Cell;
class FreeSpace;

class Passage : public FreeSpace {
public:
  virtual bool isTile();
  virtual void notifyDisplay(TextDisplay&);
};

#endif
