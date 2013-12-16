#include <iostream>
#include "waDecorator.h"
using namespace std;

waDecorator::waDecorator(PC* pc):Decorator(pc) {}

unsigned int waDecorator::getAtk() const {
  //cout << getAtk() << endl;
  if ((pc->getAtk() - 5) < 0) return 0;
  else return (pc->getAtk() - 5); 
}
