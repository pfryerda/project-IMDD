#include <string>
#include "potion.h"

Potion::~Potion() {}
bool Potion::isPotion() { return true; }
char Potion::getID() { return 'P'; }
Potion* Potion::makePositive() { return this; }
