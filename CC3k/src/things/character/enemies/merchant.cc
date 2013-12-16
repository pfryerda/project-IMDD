#include <iostream>
#include <string>
#include "merchant.h"
using namespace std;

Merchant::Merchant():            Enemy(30, 70, 5), hasThePlayerHurtMyFriends(false)   {}
Merchant::Merchant(bool hostile):Enemy(30, 70, 5), hasThePlayerHurtMyFriends(hostile) {}
char Merchant::getID()       { return 'M'; }
string Merchant::getName()   { return "Merchant"; }
bool Merchant::isHostile()   { 
  cout << "In Merchant isHostile()" << endl;
  cout << hasThePlayerHurtMyFriends << endl;
  return hasThePlayerHurtMyFriends; 
}
bool Merchant::isMerchant()  { return true; }
void Merchant::makeHostile() { hasThePlayerHurtMyFriends = true; }
