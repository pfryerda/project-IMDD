#ifndef __DWARF_H__
#define __DWARF_H__
#include <string>
#include "pc.h"

class Gold;

class Dwarf : public PC {
public:
  Dwarf();
  virtual void collectGold(Gold*&);
  virtual std::string getName();
};

#endif
