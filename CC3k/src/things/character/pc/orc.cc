#include <string>
#include "../character.h"
#include "orc.h"
#include "../../item/gold/gold.h"
using namespace std;

Orc::Orc(): PC(180, 30, 25) {}
void Orc::collectGold(Gold*& g) { Money += ((static_cast<float>(g->getAmount()))/2); }
string Orc::getName() { return "Orc"; }
