#include <string>
#include "../character.h"
#include "human.h"
using namespace std;

Human::Human(): PC(140, 20, 20) {}
unsigned int Human::getFinalScore() { return (1.5)*getCurrScore(); }
string Human::getName() { return "Human"; }
