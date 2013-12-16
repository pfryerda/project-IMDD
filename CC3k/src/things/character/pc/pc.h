#ifndef __PC_H__
#define __PC_H__
#include <string>
#include <map>
#include "../character.h"
#include "../../item/potion/potion.h"

class Gold;

class PC : public Character {
protected:
  const unsigned int MaxHP;
  unsigned int chamberNum;
  unsigned int Money;
  std::map<std::string, bool> discoveredPotions;
public:
  PC(unsigned int, unsigned int, unsigned int);
  virtual ~PC() = 0;

  virtual unsigned int getMaxHP() const;
  virtual PC* removePotionEffects();

  virtual char getID();
  virtual bool isPlayer();
  virtual bool isElf();

  virtual int strike(Character*);
  PC* drinkPotion(Potion *&);

  virtual void makePotionDiscovered(std::string);
  virtual bool getDiscoveredPotion(std::string);
  virtual void collectGold(Gold*&);

  virtual void setChamberNum(int);
  virtual int getChamberNum();

  virtual unsigned int getCurrScore();
  virtual unsigned int getFinalScore();
};

#endif
