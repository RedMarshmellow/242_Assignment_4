#ifndef INC_242_ASSIGNMENT_4_WARRIOR_H
#define INC_242_ASSIGNMENT_4_WARRIOR_H
#include <vector> //used to store kill list
#include <string>
#include "zombie.h"
//warrior classes here
class warrior:public entity {
protected:
    enum warriorTypes{DERICK,CHICHONNE} warriorType;
    bool alive;
    int hitPoints;
    int ammo;
    std::string killList;
    int score;
public:
    warrior(char representingChar, int ammo, enum warriorTypes warriorType);
    void addScore(int addition);

    virtual void addKill(entity* zombieKilled);
    bool isAlive() const;
    int getHitPoints() const;
    int getAmmo() const;

    const std::string & getKillList() const;

    int getScore() const;
};

class derick:public warrior {
public:
    int shootBullets(); //derick will always to attempt to shoot 2 bullets if he can
    derick();
};

class chichonne: public warrior{
private:
public:
    chichonne();

private:
    bool megaKatana; // bool is false when katana is unleveled, true when katana is level to megaKatana
    int katanaKills=0; // to check for katana upgrade
public:
    int shootBullet();

    void addKill(entity *zombieKilled) override;

    int swipeKatana() const;
    bool confirmKatanaKill();
};

#endif //INC_242_ASSIGNMENT_4_WARRIOR_H
