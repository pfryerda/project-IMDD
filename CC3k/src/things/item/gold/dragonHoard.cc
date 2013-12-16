#include "dragonHoard.h"
using namespace std;

DragonHoard::DragonHoard():isMyDaddyDead(false) {}
string DragonHoard::getName() { return "dragon hoard"; }
int DragonHoard::getAmount()  { return 6; }
bool DragonHoard::canPickUp() { return isMyDaddyDead; }
void DragonHoard::notify()    { isMyDaddyDead = true; }
