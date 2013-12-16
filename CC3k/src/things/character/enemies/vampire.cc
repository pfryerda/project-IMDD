#include <string>
#include "vampire.h"
using namespace std;

Vampire::Vampire():Enemy(50, 25, 25) {}
char Vampire::getID() { return 'V'; }
string Vampire::getName() { return "Vampire"; }
