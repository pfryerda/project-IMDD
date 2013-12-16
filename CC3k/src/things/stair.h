#ifndef __STAIR_H__
#define __STAIR_H__
#include <string>
#include "thing.h"

class Stairs : public Thing {
  unsigned int chamberNum;
public:
  Stairs();
  virtual char getID();
  virtual std::string getName();
  virtual bool isStairs();
  void setChamberNum(int);
  unsigned int getChamberNum();
};

#endif
