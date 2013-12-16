#include <string>
#include "werewolf.h"
using namespace std;

Werewolf::Werewolf():Enemy(120, 30, 5) {}
char Werewolf::getID() { return 'W'; }
string Werewolf::getName() { return "Werewolf"; }
