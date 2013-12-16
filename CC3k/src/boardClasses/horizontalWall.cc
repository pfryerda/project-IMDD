#include "textDisplay.h"
#include "cell.h"
#include "horizontalWall.h"
using namespace std;

void HorizontalWall::notifyDisplay(TextDisplay& td) { td.notify(r(), c(), '-'); }
