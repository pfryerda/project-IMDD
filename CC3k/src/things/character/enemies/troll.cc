#include <string>
#include "troll.h"
using namespace std;

Troll::Troll():Enemy(120, 25, 15) {}
char Troll::getID() { return 'T'; }
string Troll::getName() { return "Troll"; }
