#ifndef INC_242_ASSIGNMENT_4_ZOMBIE_H
#define INC_242_ASSIGNMENT_4_ZOMBIE_H

#include "entity.h"
#include <iostream>

enum type{S,M,L};

class zombie : public entity{
private:
    type    zombieclass;
    int     HP;
    int     DMG;
    bool    KO;
public:
    zombie(int size);

    type getZombieclass() const;

    int getHp() const;

    int getDmg() const;

    void updateHP(int);

    bool isKO() const;

    void printInfo(int);
};


#endif
