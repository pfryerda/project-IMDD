#ifndef __TEXTDISPLAY_H__
#define __TEXTDISPLAY_H__
#include <iostream>
#include <vector>

const int NUMROWS = 25;
const int NUMCOLUMNS = 79;

class TextDisplay {
  std::vector< std::vector<char> > theDisplay;
public:
  TextDisplay();
  void notify(int, int, char);

  friend std::ostream& operator<<(std::ostream&, const TextDisplay&);
};

#endif
