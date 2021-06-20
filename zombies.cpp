#include "zombies.h"

type zombies::getZombieclass() const {
    return zombieclass;
}

int zombies::getHp() const {
    return HP;
}

int zombies::getDmg() const {
    return DMG;
}

void zombies::updateHP(int dmg) {
    this->HP -= dmg;
    if(this->HP <= 0)
        this->KO = true;
}

bool zombies::isKO() const {
    return KO;
}

zombies::zombies(int size, char representingChar) : entity(size, representingChar) {

    switch (representingChar) {
        case 'S':
            zombieclass = S;
            HP = 4;
            DMG = 2;
            KO = false;
            break;
        case 'M':
            zombieclass = M;
            HP = 8;
            DMG = 4;
            KO = false;
            break;
        case 'L':
            zombieclass = L;
            HP = 12;
            DMG = 8;
            KO = false;
            break;
        default:
            throw "UNDEFINED ZOMBIE TYPE\n";
    }
}
