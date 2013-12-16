#include "textDisplay.h"
#include "cell.h"
#include "freeSpace.h"
#include "door.h"
using namespace std;

void Door::notifyDisplay(TextDisplay& td) {
  if (th==NULL) td.notify(r(), c(), '+');
  else td.notify(r(), c(), '@');
}
