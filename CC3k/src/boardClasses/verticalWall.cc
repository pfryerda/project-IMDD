#include "textDisplay.h"
#include "cell.h"
#include "verticalWall.h"
using namespace std;

void VerticalWall::notifyDisplay(TextDisplay& td) { td.notify(r(), c(), '|'); }
