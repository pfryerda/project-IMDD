#include "textDisplay.h"
#include "cell.h"
#include "emptySpace.h"
using namespace std;

void EmptySpace::notifyDisplay(TextDisplay& td) { td.notify(r(), c(), ' '); }
