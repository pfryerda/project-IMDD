#include <string>
#include "goblin.h"
using namespace std;

Goblin::Goblin():Enemy(70, 5, 10) {}
char Goblin::getID() { return 'N'; }
string Goblin::getName() { return "Goblin"; }
