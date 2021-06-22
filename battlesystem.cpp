#include "battlesystem.h"
#include <iostream>
#include <cmath>

using std::cout; using std::cin;

int rollDice() {
    return rand() % 6 + 1;
}

int calcDMG(int base, int dice) {
    if (dice >= 5)
        return base * 10;
    else if (dice <= 2)
        return base*2;
    else
        return base*5;
}



int battle(warrior *Warrior, zombie *Zombie) {
    //function to perform the battle gameplay
    //returns 0 if player wins
    //returns 1 if zombie wins

    char selection;
    cout << "Zombie Encounter!\n";
    while (Warrior->isAlive() && !Zombie->isKO()) {
        cout << Warrior;
        Zombie->printInfo(1);
        Warrior->printOptions();
        cin >> selection;
        playerAttack(selection, Warrior,Zombie);
        if (Zombie->isKO())
            break;
        Zombie->printInfo(2);
        Warrior->takeDamage(Zombie->getDmg());
    }
    if (Zombie->isKO()) {
        Zombie->printInfo(3);
        Warrior->addKill(Zombie);
        cout << "Score: " << Warrior->getScore();
        return 0;
    }
    if (!Warrior->isAlive()) {
        (Warrior->getWarriorType() == CHICHONNE) ? cout << "Chichonne " : cout << "Derek ";
        cout << "Has Been Defeated!\n";
        return 1;
    }
}

void playerAttack(char attack,warrior* Warrior,zombie* Zombie) {
    if (attack == 'K') {
        (Warrior->getWarriorType()==CHICHONNE) ? cout << "Chichonne Strikes At The Zombie With Her Katana!\n" : cout << "Derek Desperately Slashes The Zombie With His Knife!\n";
        Zombie->updateHP(Warrior->melee());
    } else {
        (Warrior->getWarriorType() == CHICHONNE) ? cout << "Chichonne Fires Her Pistol!\n" : cout << "Derek Fires His Revolver!\n";
        Zombie->updateHP(calcDMG(Warrior->shoot(),rollDice()));
    }
}