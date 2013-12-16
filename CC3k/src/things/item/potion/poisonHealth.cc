#include <string>
#include "poisonHealth.h"
#include "restoreHealth.h"
#include "../../character/pc/pc.h"
using namespace std;

PC* PoisonHealth::applyEffect(PC* player) {
  if ((player->getHP() - 5) <= 0) player->setHP(0);
  else player->setHP(player->getHP() - 5);
  return player;
}

string PoisonHealth::getName() { return "PH"; }

Potion* PoisonHealth::makePositive() {
  return new RestoreHealth();
}
