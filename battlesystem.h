#ifndef INC_242_ASSIGNMENT_4_BATTLESYSTEM_H
#define INC_242_ASSIGNMENT_4_BATTLESYSTEM_H

#include "warrior.h"
#include "entity.h"

int battle(warrior* , zombie* );
int rollDice();
int calcDMG(int, int);
void playerAttack(char,warrior*,zombie*);
void printMessage();
#endif
