#include "baDecorator.h"
using namespace std;

baDecorator::baDecorator(PC* pc):Decorator(pc) {}

unsigned int baDecorator::getAtk() const { return (pc->getAtk() + 5); }
