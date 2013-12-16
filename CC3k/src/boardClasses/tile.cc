#include "textDisplay.h"
#include "cell.h"
#include "freeSpace.h"
#include "tile.h"
#include "../things/thing.h"
using namespace std;

Tile::Tile() {}
Tile::Tile(Thing* t):FreeSpace(t) {}
bool Tile::isTile() { return true; }
void Tile::notifyDisplay(TextDisplay& td) {
  if (th==NULL) td.notify(r(), c(), '.');
  else td.notify(r(), c(), th->getID());
}
