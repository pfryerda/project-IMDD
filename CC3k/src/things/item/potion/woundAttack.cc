#include <string>
#include "woundAttack.h"
#include "boostAttack.h"
#include "../../character/pc/pc.h"
#include "../../character/pc/decorator/waDecorator.h"
using namespace std;

PC* WoundAttack::applyEffect(PC* player) { 
  return new waDecorator(player);
}

string WoundAttack::getName() { return "WA"; }

Potion* WoundAttack::makePositive() {
  return new BoostAttack();
}
