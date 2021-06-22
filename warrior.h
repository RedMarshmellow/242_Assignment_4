#ifndef INC_242_ASSIGNMENT_4_WARRIOR_H
#define INC_242_ASSIGNMENT_4_WARRIOR_H
#include <vector> //used to store kill list
#include <string>
#include <ostream>
#include "zombie.h"

//warrior classes here

enum warriorTypes{DERICK,CHICHONNE};

class warrior:public entity {
private:
    enum warriorTypes warriorType;
    bool alive;
    int hitPoints;
    int ammo;
    std::string killList;
    int score;
protected:
    bool have2Kills(); //only want chichonne to access this;
public:
    warrior(char representingChar, int ammo, enum warriorTypes warriorType);

    virtual void printOptions() = 0;

    virtual int shoot() = 0;

    virtual int melee() const = 0;

    virtual void addKill(entity* zombieKilled);
    bool isAlive() const;
    int getHitPoints() const;
    int getAmmo() const;

    void addScore(int addition);
    void consumeAmmo(int ammo);
    void addAmmo(int amount);
    void heal(int hitPoints);
    void takeDamage(int hitPoints);

    const std::string & getKillList() const;

    int getScore() const;
};

class derick:public warrior {
public:
    int shoot() override; //derick will always to attempt to shoot 2 bullets if he can
    int melee() const override;
    derick();
    friend std::ostream &operator<<(std::ostream &os, const derick &derick);

    void printOptions() override;
};

class chichonne: public warrior{
private:
public:
    chichonne();

private:
    bool megaKatana; // bool is false when katana is unleveled, true when katana is level to megaKatana
public:
    int shoot()override;

    friend std::ostream &operator<<(std::ostream &os, const chichonne &chichonne);

    void addKill(entity *zombieKilled) override;

    int melee() const override;

    void printOptions() override;
};

#endif //INC_242_ASSIGNMENT_4_WARRIOR_H
