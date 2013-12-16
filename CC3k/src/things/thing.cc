#include "thing.h"

Thing::~Thing() {}
bool Thing::canPickUp()  { return false; }
bool Thing::isGold()     { return false; }
bool Thing::isPotion()   { return false; }
bool Thing::isPlayer()   { return false; }
bool Thing::isEnemy()    { return false; }
bool Thing::isMerchant() { return false; }
bool Thing::isDragon()   { return false; }
bool Thing::isStairs()   { return false; }
