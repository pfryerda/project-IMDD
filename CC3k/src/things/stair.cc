#include "stair.h"
using namespace std;

Stairs::Stairs():chamberNum(5) {}
char Stairs::getID()     { return '/'; }
string Stairs::getName() { return "stair case"; }
bool Stairs::isStairs()  { return true; }
void Stairs::setChamberNum(int n) { chamberNum = n; }
unsigned int Stairs::getChamberNum() { return chamberNum; }
