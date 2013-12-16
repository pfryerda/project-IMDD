#include "textDisplay.h"
#include "cell.h"
#include "freeSpace.h"
#include "passage.h"
using namespace std;

bool Passage::isTile() { return false; }
void Passage::notifyDisplay(TextDisplay& td) {
  if (th==NULL) td.notify(r(), c(), '#');
  else          td.notify(r(), c(), '@');
}
