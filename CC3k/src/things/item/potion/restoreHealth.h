#ifndef __RESTOREHEALTH_H__
#define __RESTOREHEALTH_H__

#include "potion.h"
#include <string>

class RestoreHealth : public Potion {
public:
  virtual PC* applyEffect(PC*);
  virtual std::string getName();
};

#endif
