#include <string>
#include "restoreHealth.h"
#include "../../character/pc/pc.h"

using namespace std;

PC* RestoreHealth::applyEffect(PC* player) {
  if ((player->getHP() + 5) >= player->getMaxHP()) player->setHP(player->getMaxHP());
  else player->setHP(player->getHP() + 5);
  return player;
}

string RestoreHealth::getName() { return "RH"; }
