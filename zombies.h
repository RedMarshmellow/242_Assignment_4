#ifndef INC_242_ASSIGNMENT_4_ZOMBIES_H
#define INC_242_ASSIGNMENT_4_ZOMBIES_H

#include "entity.h"

enum type{S,M,L};

class zombies : public entity{
private:
    type    zombieclass;
    int     HP;
    int     DMG;
    bool    KO;
public:
    zombies(int size, char representingChar);

    type getZombieclass() const;

    int getHp() const;

    int getDmg() const;

    void updateHP(int);

    bool isKO() const;
};


#endif
