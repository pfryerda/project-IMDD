#include <iostream>
#include <string>
#include "../character.h"
#include "elf.h"
#include "../../item/potion/potion.h"
using namespace std;

Elf::Elf(): PC(140, 30, 10) {}

string Elf::getName() { return "Elf"; }

bool Elf::isElf() { return true; }
