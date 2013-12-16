#include <iostream>
#include <vector>
#include "textDisplay.h"
using namespace std;

TextDisplay::TextDisplay() {
  for (int i = 0; i < NUMROWS; ++i) {
    vector<char> row;
    for (int j = 0; j < NUMCOLUMNS; ++j) row.push_back(' ');
    theDisplay.push_back(row);
  }
}

void TextDisplay::notify(int r,int c,char t) { theDisplay[r][c] = t; }

ostream& operator<<(ostream& out, const TextDisplay& td) {
  for (unsigned int i = 0; i < td.theDisplay.size(); ++i) {
    for (unsigned int j = 0; j < td.theDisplay[i].size(); ++j) out << td.theDisplay[i][j];
    if (i+1 < td.theDisplay.size()) out << endl;
  }
  return out;
}
