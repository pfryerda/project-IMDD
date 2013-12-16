#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <stdlib.h>
#include "game.h"
using namespace std;

int main(int argc, char* argv[]) {
  srand(time(NULL));

  //Gets proper map from command line
  fstream* mapPath = NULL;
  string defaultMap = "maps/default.txt";
  if (argc <= 1) mapPath = new fstream(defaultMap.c_str());
  else           mapPath = new fstream(argv[1]);

  Game* g = Game::getInstance(mapPath);

  string input = "";
  if (!g->done()) {
    while (cin >> input) {
      if      (input == "q" || input == "quit" || input == ".") break;
      else if (input == "u" || input == "use" || input == "5") {
        cin >> input; //Direction
        g->playerDrink(input);
      }
      else if (input == "a" || input == "attack" || input == "0") {
        cin >> input; //Direction
        g->playerAttack(input);
      }
      else if (input == "h" || input == "help" || input == "/") { 
        g->clearScreen();
        g->displayHelp(cout);
        cout << endl;
      }
      else if (input == "l" || input == "legend" || input == "*") {
        g->clearScreen();
        g->displayLegend(cout);
        cout << endl;
      }
      else if (input == "th" || input == "togglehelp" || input == "/-") {
       g->toggleHelp();
       g->clearScreen();
       cout << *g << endl;
      }
      else if (input == "tl" || input == "togglelegend" || input == "*-") {
        g->toggleLegend();
        g->clearScreen();
        cout << *g << endl;
      }
      else if (input == "r" || input == "restart" || input == "+") g->restart();
      else g->playerMove(input);
  
      if (g->done()) break;
    }
  }

  delete mapPath;
  return 0; 
}
