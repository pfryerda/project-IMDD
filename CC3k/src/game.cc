#include <iostream>
#include <unistd.h>
#include <pwd.h>
#include <sstream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <vector>
#include <set>

#include "game.h"
#include "boardClasses/cell.h"
#include "boardClasses/floor.h"
#include "things/character/enemies/enemy.h"
#include "things/character/enemies/merchant.h"
#include "things/character/enemies/dragon.h"
#include "things/character/pc/human.h"
#include "things/character/pc/dwarf.h"
#include "things/character/pc/orc.h"
#include "things/character/pc/elf.h"
#include "things/item/gold/merchantHoard.h"
using namespace std;

class TextDisplay;
class PC;

Game* Game::instance = NULL;
Game::Game(fstream* map):gameRunning(true), hostileMerchants(false), tHelp(false), tLegend(false), firstTime(true) {
  set<Cell*> emptySet;
  enemies = emptySet;
  PlayerCell = NULL;
  stairs = NULL;
  PC *Player = buildPlayer();
  if (Player != NULL) {
    currLevel = new Floor(map, Player, this);
    if (PlayerCell != NULL) PlayerCell->notifyNeighbours();
    buildGame(1, Player);
  }
}


Game::~Game() {}

void Game::CleanUp (void) {
  delete instance->currLevel;
  delete instance;
}

Game* Game::getInstance(fstream* file) {
  if (instance == NULL) {
    instance = new Game(file);
    atexit(CleanUp);
  }
  return instance;
}


bool Game::done() const { return !gameRunning; }

void Game::restart() {
  currLevel->clearGrid();
  enemies.clear();
  hostileMerchants = false;
  PlayerCell->notifyNeighbours();
  PlayerCell = NULL;
  PC *Player = buildPlayer();
  if (Player != NULL) {
    stairs = NULL;
    buildGame(1, Player);
  }
}

void Game::nextLevel() {
  if (currLevelNum == NUMLEVELS) gameOver(true);
  else {
    PC *Player = static_cast<PC*>(PlayerCell->removeOccupant());
    Player = Player->removePotionEffects();
    PlayerCell->notifyNeighbours();
    PlayerCell = NULL;
    currLevel->clearGrid();
    stairs = NULL;
    buildGame(currLevelNum+1, Player);
  }
}

void Game::gameOver(bool win) {
  cout << endl;
  if(win) cout << "Congratulations you have won!" << endl;
  else    cout << "Game Over!" << endl;
  PC *Player = static_cast<PC*>(PlayerCell->removeOccupant());
  PlayerCell->addOccupant(Player);
  cout << "Name: " << (getpwuid(getuid()))->pw_name << endl;
  cout << "Race: " << Player->getName() << endl;
  cout << "Final Score: " << Player->getFinalScore() << endl;
  cout << "Play again? Yes(y), No(n)" << endl;
  string choice;
  while (true) {
    cin >> choice;
    if (choice == "y" || choice == "yes" || choice == "1") {
      restart();
      break;
     }
     else if (choice == "n" || choice == "no" || choice == "0")  {
       gameRunning = false;
       break;
     }
     else cout << "Invalid choice" << endl;
  }
}

void Game::buildGame(int n, PC *Player) {
  currLevelNum = n;
  if (stairs == NULL) {
    stairs = new Stairs();
    stairs->setChamberNum(5);
  }
  if(PlayerCell == NULL) {
    if (stairs == NULL) PlayerCell = currLevel->generatePlayer(Player, 5);
    else PlayerCell = currLevel->generatePlayer(Player, stairs->getChamberNum());
  }
  enemies = currLevel->generate(enemies, stairs, hostileMerchants, Player->getChamberNum());
  clearScreen();
  if (firstTime) {
    displayHelp(cout);
    cout << "Player has spawned" << PlayerCell->getNeighbourNames() << endl;
    firstTime = false;
  } else {
    cout << *this << "Player has spawned" << PlayerCell->getNeighbourNames() << endl;
  }
}

PC* Game::buildPlayer() {
  string choice;
  PC* Player = NULL;
  clearScreen();
  cout << "Choose your class" << endl;
  cout << "Race      HP   Atk Def Special" << endl;
  cout << "-------------------------------------------------------------" << endl;
  cout << "Human(h)  140  20  20  End score is doubled." << endl;
  cout << "Orc  (o)  180  30  25  Gold collected is worth half." << endl;
  cout << "Dwarf(d)  100  20  30  Gold collected is worth double." << endl;
  cout << "Elf  (e)  140  30  10  Negative potions give positive effect." << endl;
  cout << "Quit (q)" << endl;
  while (Player == NULL) {
    cin >> choice;
    if      (choice == "h" || choice == "human" || choice == "1") Player = new Human();
    else if (choice == "o" || choice == "orc"   || choice == "2") Player = new Orc();
    else if (choice == "d" || choice == "dwarf" || choice == "3") Player = new Dwarf();
    else if (choice == "e" || choice == "elf"   || choice == "4") Player = new Elf();
    else if (choice == "quit" || choice == "q") {
      gameRunning = false; 
      break;
    }
    else cout << "Not a valid choice" << endl; 
  }
  return Player;
}

void Game::playerMove(string dir) {
  TextDisplay* td = currLevel->getDisplay();
  string actionMsg = "PC moves ";
  pair<Cell*, string> movementInfo = PlayerCell->getNeighbour(dir, actionMsg);
  Cell* newCell = movementInfo.first;
  actionMsg = movementInfo.second;

  vector<string> neighbourNames;
  if (newCell != NULL && newCell->containsStairs()) nextLevel();
  else {
    if (newCell != NULL) {
      if (PlayerCell->move(newCell, td)) {
        PlayerCell->notifyNeighbours();
        PlayerCell = newCell;
        PlayerCell->notifyNeighbours();
        actionMsg += PlayerCell->getNeighbourNames();
        actionMsg += ".";
        actionMsg += stepEnemy();
      } 
      else actionMsg = "Invalid command: You can not walk on that space";
    }
    clearScreen();
    cout << *this << actionMsg << endl;
    PC *Player = static_cast<PC*>(PlayerCell->removeOccupant());
    PlayerCell->addOccupant(Player);
    if (Player->isDead()) gameOver(false);
  }
}

void Game::playerAttack(string dir) {
  TextDisplay* td = currLevel->getDisplay();
  pair<Cell*, string> attackInfo = PlayerCell->getNeighbour(dir, "");
  stringstream actionMsg;
  Cell* opponent = attackInfo.first;

  if (opponent != NULL) {
    if (opponent->isTile() && opponent->occupied()) {
      Thing* o = opponent->removeOccupant();
      if (o->isEnemy()) {
        Enemy* e = static_cast<Enemy*>(o);
        if (e->isMerchant() && !(e->isHostile())) {
          hostileMerchants = true;
          notifyMerchants();
          Merchant* m = static_cast<Merchant*>(e);
          m->makeHostile();
          e=m;
        }
        PC *Player = static_cast<PC*>(PlayerCell->removeOccupant());
        int dmg = Player->strike(e);
        PlayerCell->addOccupant(Player);
        actionMsg << "PC deals " << dmg << " damage to " << e->getName() << " (" << e->getHP() << " HP).";
        if (e->isDead() && e->isMerchant()) {
          delete e;
          opponent->addOccupant(new MerchantHoard());
          actionMsg << " PC sees a merchant hoard.";
        }
        else if (e->isDead() && e->isDragon()) {
          static_cast<Dragon*>(e)->notifyGold();
          delete e;
        }
        else if (e->isDead()) delete e;
        else opponent->addOccupant(o);
        opponent->notifyDisplay(*td);
        actionMsg << stepEnemy();
      } else {
        opponent->addOccupant(o);
        actionMsg << "Invalid command: There is no enemy in that space";
      }
    }
    else actionMsg << "Invalid command: There is no enemy in that space";
  }
  else actionMsg << "Invalid command: use no,so,ea,we,ne,nw,se,sw to choose who to attack";
  clearScreen();
  cout << *this << actionMsg.str() << endl;
  PC *Player = static_cast<PC*>(PlayerCell->removeOccupant());
  PlayerCell->addOccupant(Player);
  if (Player->isDead()) gameOver(false);
}

void Game::playerDrink(string dir) {
  TextDisplay* td = currLevel->getDisplay();
  stringstream actionMsg;
  pair<Cell*, string> drinkInfo = PlayerCell->getNeighbour(dir, "");
  Cell* pot = drinkInfo.first;

  if (pot != NULL) {
    if (pot->isTile() && pot->occupied()) {
      Thing* p = pot->removeOccupant();
      if (p->isPotion()) {
        PC* Player = static_cast<PC*>(PlayerCell->removeOccupant());
        Potion* P = static_cast<Potion*>(p);
        Player = Player->drinkPotion(P);
        actionMsg << "PC drinks a " << P->getName() << " potion";
        delete P;
        pot->notifyDisplay(*td);
        PlayerCell->addOccupant(Player);
        string neighbourNames = PlayerCell->getNeighbourNames();
        if (neighbourNames == "") actionMsg << ".";
        else                      actionMsg << neighbourNames;
        actionMsg << stepEnemy();
      } else {
        pot->addOccupant(p);
        actionMsg << "Invalid command: There is no potion in that space";
      }
    }
    else actionMsg << "Invalid command: There is no potion in that space";
  }
  else actionMsg << "Invalid command: use no,so,ea,we,ne,nw,se,sw to choose where to drink";
  clearScreen(); 
  cout << *this << actionMsg.str() << endl;
  PC *Player = static_cast<PC*>(PlayerCell->removeOccupant());
  PlayerCell->addOccupant(Player);
  if (Player->isDead()) gameOver(false);
}

string Game::stepEnemy() {
  set<Cell*> newSet;
  stringstream actionMsg;
  TextDisplay* td = currLevel->getDisplay();
  for (set<Cell*>::iterator i = enemies.begin(); i != enemies.end(); ++i) {
    if((*i)->occupied()) {
      Thing* th = (*i)->removeOccupant();
      (*i)->addOccupant(th);
      if (th->isEnemy()) {
        Enemy* e = static_cast<Enemy*>(th);
        if((*i)->isPlayerNearBy() && e->isHostile()) {
          int ranNum = rand() % 2;
          if (ranNum == 0) {
            PC *Player = static_cast<PC*>(PlayerCell->removeOccupant());
            int dmg = e->strike(Player);
            actionMsg << " " << e->getName() << " deals " << dmg << " damage to PC (" << Player->getHP() << " HP).";
            PlayerCell->addOccupant(Player);
          } else {
            actionMsg << " " << e->getName() << " attacks the PC but misses.";
          }
          newSet.insert(*i);
        }
        else if((*i)->numAvaliableNeighbours() != 0 && e->canMove()) {
          Cell* newCell = NULL;
          while(newCell == NULL) {
            newCell = (*i)->getRandNeighbour();
            if (newCell->occupied() || !(newCell->isTile())) newCell = NULL;
            else (*i)->move(newCell, td);
          }
          newSet.insert(newCell);
        }
        else newSet.insert(*i);
      }
    }
  }
  enemies = newSet;
  return actionMsg.str();
}

void Game::notifyMerchants() {
  for (set<Cell*>::iterator i = enemies.begin(); i != enemies.end(); ++i) {
    if((*i)->occupied()) {
      Thing* th = (*i)->removeOccupant();
      if (th->isMerchant()) {
        Merchant* m = static_cast<Merchant*>(th);
        m->makeHostile();
        (*i)->addOccupant(m);
      } else {
        (*i)->addOccupant(th);
      }
    }
  }
}

void Game::addEnemy(Cell* c)      { enemies.insert(c); }
void Game::setPlayerCell(Cell* c) { PlayerCell = c; }
void Game::setStairs(Stairs* s)   { stairs  = s; }

void Game::toggleHelp() {
  tHelp = !tHelp;
  tLegend = false;
}
void Game::toggleLegend() {
  tLegend = !tLegend;
  tHelp = false;
}

ostream& Game::displayHelp(ostream& out) const {
  out << "Command                  Descirption                      " << endl;
  out << "----------------------------------------------------------" << endl;
  out << "no,so,ea,we,ne,nw,se,sw  Move in given direction          " << endl;
  out << "use(u) <direction>       Use potion in given direction    " << endl;
  out << "attack(a) <direction>    Attack in given direction        " << endl;
  out << "help(h)                  Display this help box            " << endl;
  out << "togglehelp(th)           Toggle help to always display    " << endl;
  out << "legend(l)                Display a legend                 " << endl;
  out << "togglelegend(tl)         Toggle legend to always display  " << endl;
  out << "restart(r)               Restarts game back to race select" << endl;
  out << "quit(q)                  Quits the game session           " << endl;
  out << endl;
  return gamePrint(out);
}

ostream& Game::displayLegend(ostream& out) const {
  out << "Key   Title         Key   Title         Key   Title     " << endl;
  out << "---------------     ---------------     --------------------- " << endl;
  out << "/     Stairs        @     Player        RH    Restore Health  " << endl;
  out << "G     Gold          V     Vampire       PH    Poison Health   " << endl;
  out << "P     Potion        W     Werewolf      BA    Boost Attack    " << endl;
  out << "+     Door          T     Troll         BD    Boot Defence    " << endl;
  out << "-     Wall          N     Goblin        WA    Wound Attack    " << endl;
  out << "|     Wall          X     Phoenix       WD    Wound Defence   " << endl;
  out << "#     Passage       D     Dragon                              " << endl;
  out << ".     Tile          M     Merchant                            " << endl;
  out << endl;
  return gamePrint(out);
}

void Game::clearScreen() const { cout << string(60, '\n'); }

ostream& Game::gamePrint(ostream& out) const {
  PC * Player = static_cast<PC*>(PlayerCell->removeOccupant());
  out << "Player: " << (getpwuid(getuid()))->pw_name << endl;
  out << *currLevel << endl;
  out << "Race: " << Player->getName();
  out << " Gold: " << Player->getCurrScore();

  unsigned int digits = 1, tracker = 10;
  while(tracker <= Player->getCurrScore()) tracker*=10, ++digits;
  unsigned int numSpaces = 58 - Player->getName().length() - digits;

  for (unsigned int i = 0; i <= numSpaces; ++i) cout << " ";
  out << "Floor " << currLevelNum << endl;
  out << *Player << endl;
  PlayerCell->addOccupant(Player);
  return out << "Action: ";
}
string Luke = "awesome";

ostream& operator<<(ostream& out, const Game& g) {
  if      (g.tHelp)   return g.displayHelp(out);
  else if (g.tLegend) return g.displayLegend(out);
  else                return g.gamePrint(out);
}
