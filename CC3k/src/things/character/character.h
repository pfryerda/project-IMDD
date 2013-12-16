#ifndef __CHARACTER_H__
#define __CHARACTER_H__
#include <string>
#include "../thing.h"

class Character : public Thing {
  unsigned int HP;
  const unsigned int Atk;
  const unsigned int Def;

public:
  Character(unsigned int,unsigned int, unsigned int);
  virtual ~Character() = 0;

  virtual void setHP(unsigned int);
  virtual unsigned int getHP() const;
  virtual unsigned int getAtk() const;
  virtual unsigned int getDef() const;

  virtual char getID() = 0;
  virtual std::string getName() = 0;
  virtual int strike(Character*);
  int damage(int);
  bool isDead();

  friend std::ostream& operator<<(std::ostream&, const Character&);
};

#endif
