#ifndef __ITEM_H__
#define __ITEM_H__
#include <string>
#include "../thing.h"

class Item : public Thing {
public:
  virtual ~Item() = 0;

  virtual char getID() = 0;
  virtual std::string getName() = 0;
};

#endif
