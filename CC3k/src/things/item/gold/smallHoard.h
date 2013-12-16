#ifndef __SMALLHOARD_H__
#define __SMALLHOARD_H__
#include "gold.h"


class SmallHoard : public Gold {
public:
  virtual std::string getName();
  virtual int getAmount();
};

#endif
