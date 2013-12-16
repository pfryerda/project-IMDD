#include <string>
#include "../character.h"
#include "dwarf.h"
#include "../../item/gold/gold.h"
using namespace std;

Dwarf::Dwarf(): PC(100, 20, 30) {}
void Dwarf::collectGold(Gold*& g) { Money += 2*g->getAmount(); }
string Dwarf::getName() { return "Dwarf"; }
