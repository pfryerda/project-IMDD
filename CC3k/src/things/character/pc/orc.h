#ifndef __ORC_H__
#define __ORC_H__
#include <string>
#include "pc.h"

class Gold;

class Orc : public PC {
public:
  Orc();
  virtual void collectGold(Gold*&);
  virtual std::string getName();
};

#endif
