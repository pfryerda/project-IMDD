#ifndef __DOOR_H__
#define __DOOR_H__
#include "freeSpace.h"

class TextDisplay;
class Cell;

class Door : public FreeSpace {
public:
  virtual void notifyDisplay(TextDisplay& td);
};

#endif
