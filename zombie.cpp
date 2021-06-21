#include "zombie.h"

type zombie::getZombieclass() const {
    return zombieclass;
}

int zombie::getHp() const {
    return HP;
}

int zombie::getDmg() const {
    return DMG;
}

void zombie::updateHP(int dmg) {
    this->HP -= dmg;
    if(this->HP <= 0)
        this->KO = true;
}

bool zombie::isKO() const {
    return KO;
}

zombie::zombie(int size) : entity(size) {
    if(size==1)
        setRepresentingChar('S');
    else if (size==2)
        entity::setRepresentingChar('M');
    else if (size==3)
        entity::setRepresentingChar('L');
    switch (size) {
        case 1:
            zombieclass = S;
            HP = 4;
            DMG = 2;
            KO = false;
            break;
        case 2:
            zombieclass = M;
            HP = 8;
            DMG = 4;
            KO = false;
            break;
        case 3:
            zombieclass = L;
            HP = 12;
            DMG = 8;
            KO = false;
            break;
        default:
            throw "UNDEFINED ZOMBIE TYPE\n";
    }
}