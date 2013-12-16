#ifndef __ELF_H__
#define __ELF_H__
#include <string>
#include "pc.h"
#include "../../item/potion/potion.h"

class Elf : public PC {
public:
  Elf();
  virtual std::string getName();
  virtual bool isElf();
};

#endif
