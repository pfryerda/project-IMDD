#include <string>
#include "woundDefence.h"
#include "boostDefence.h"
#include "../../character/pc/pc.h"
#include "../../character/pc/decorator/wdDecorator.h"

using namespace std;

PC* WoundDefence::applyEffect(PC* player) {
  return new wdDecorator(player);
}

string WoundDefence::getName() { return "WD"; }

Potion* WoundDefence::makePositive() {
  return new BoostDefence();
}
