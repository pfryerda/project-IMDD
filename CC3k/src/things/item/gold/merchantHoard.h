#ifndef __MERCHANTHOARD_H__
#define __MERCHANTHOARD_H__
#include "gold.h"

class MerchantHoard : public Gold {
public:
  virtual std::string getName();
  virtual int getAmount();
};

#endif
