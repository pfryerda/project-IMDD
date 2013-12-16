#ifndef __HUMAN_H__
#define __HUMAN_H__
#include <string>
#include "pc.h"

class Human : public PC {
public:
  Human();
  virtual unsigned int getFinalScore();
  virtual std::string getName();
};

#endif
