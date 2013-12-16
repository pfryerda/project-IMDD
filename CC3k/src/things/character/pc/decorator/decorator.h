#ifndef __DECORATOR_H__
#define __DECORATOR_H__
#include <string>
#include "../pc.h"

class Gold;
class Potion;

class Decorator : public PC {
protected:
  PC *pc;

public:
  Decorator(PC*);
  virtual ~Decorator() = 0;

  virtual bool isElf();
  virtual std::string getName();
  virtual PC* removePotionEffects();
  virtual void makePotionDiscovered(std::string);
  virtual bool getDiscoveredPotion(std::string);
  virtual void collectGold(Gold *&);
  virtual void setChamberNum(int);
  virtual int getChamberNum();
  virtual unsigned int getCurrScore();
  virtual unsigned int getFinalScore();
  virtual unsigned int getAtk() const;
  virtual unsigned int getDef() const;
  virtual unsigned int getHP() const;
  virtual unsigned int getMaxHP() const;
  virtual void setHP(unsigned int);
};

#endif
