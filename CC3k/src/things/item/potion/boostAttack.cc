#include <string>
#include "boostAttack.h"
#include "../../character/pc/pc.h"
#include "../../character/pc/decorator/baDecorator.h"

using namespace std;

PC* BoostAttack::applyEffect(PC* player) {
  return new baDecorator(player);
}

string BoostAttack::getName() { return "BA"; }
