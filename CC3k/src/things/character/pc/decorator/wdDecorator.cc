#include "wdDecorator.h"
using namespace std;

wdDecorator::wdDecorator(PC* pc):Decorator(pc) {}

unsigned int wdDecorator::getDef() const {
  if ((pc->getDef() - 5) < 0) return 0;
  else return (pc->getDef() - 5); 
}
