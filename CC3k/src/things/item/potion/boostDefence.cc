#include <string>
#include "boostDefence.h"
#include "../../character/pc/pc.h"
#include "../../character/pc/decorator/bdDecorator.h"

using namespace std;

PC* BoostDefence::applyEffect(PC* player) {
  return new bdDecorator(player);
}

string BoostDefence::getName() { return "BD"; }
