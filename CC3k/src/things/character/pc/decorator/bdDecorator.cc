#include <iostream>
#include "bdDecorator.h"
using namespace std;

bdDecorator::bdDecorator(PC* pc):Decorator(pc) {}

unsigned int bdDecorator::getDef() const { return (pc->getDef() + 5); }
