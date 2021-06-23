#include "zombie.h"

zombieTypes zombie::getZombieclass() const {
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
    if (this->HP <= 0)
        this->KO = true;
}

bool zombie::isKO() const {
    return KO;
}

zombie::zombie(int size) : entity(size, '_', Zombie) {
    if (size == 1)
        setRepresentingChar('S');
    else if (size == 2)
        entity::setRepresentingChar('M');
    else if (size == 3)
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

void zombie::printInfo(int state) const {
    switch (state) {
        case 1:
            std::cout << "Zombie HP: " << this->getHp() << "\n===============================\n";
            break;
        case 2:
            std::cout << "Zombie Attacks for " << this->getDmg() << " Damage!\n===============================\n";
            break;
        case 3:
            std::cout << "Zombie Defeated!\n===============================\n";
            break;
        default:
            break;
    }
}
