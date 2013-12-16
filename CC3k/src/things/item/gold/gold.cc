#include "gold.h"
using namespace std;

int Gold::getAmount()  { return 1; }
char Gold::getID()     { return 'G'; }
string Gold::getName() { return "normal gold"; }
bool Gold::canPickUp() { return true; }
bool Gold::isGold()    { return true; }  // Do we need this?!
