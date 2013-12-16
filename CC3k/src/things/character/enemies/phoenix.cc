#include <string>
#include "phoenix.h"
using namespace std;

Phoenix::Phoenix():Enemy(50, 35, 20) {}
char Phoenix::getID() { return 'X'; }
string Phoenix::getName() { return "Phoenix"; }
