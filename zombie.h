#ifndef INC_242_ASSIGNMENT_4_ZOMBIE_H
#define INC_242_ASSIGNMENT_4_ZOMBIE_H

#include "entity.h"
#include <iostream>

enum zombieTypes{S,M,L};

class zombie : public entity{
private:
    zombieTypes    zombieclass;
    int     HP;
    int     DMG;
    bool    KO;
public:
    zombie(int size);

    zombieTypes getZombieclass() const;

    int getHp() const;

    int getDmg() const;

    void updateHP(int);

    bool isKO() const;

    void printInfo(int);
};


#endif
