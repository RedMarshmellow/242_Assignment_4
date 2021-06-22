
#include <iostream>
#include "warrior.h"

warrior::warrior(char representingChar, int ammo, enum warriorTypes warriorType) : warriorType(warriorType),entity(1, representingChar), hitPoints(100), ammo(ammo), score(0), alive(true) {}

void warrior::addScore(int addition) {
    score+=addition;
}

bool warrior::isAlive() const {
    return alive;
}

int warrior::getHitPoints() const {
    return hitPoints;
}

int warrior::getAmmo() const {
    return ammo;
}

int warrior::getScore() const {
    return score;
}

const std::string & warrior::getKillList() const {
    return killList;
}

void warrior::addKill(entity *zombieKilled){
    //function to automatically update score and killList from zombie entity
    //also will keep track of katana Leveling
    //note: as of writing, the function will also delete zombie object, may change later

    int size = zombieKilled->getSize() - 1;
    int scores[3] = {50,75,100};
    addScore(scores[size]);

    std::string labels[3] = {"Small Zombie","Medium Zombie","Large Zombie"};
    if (!killList.empty())
        killList+=",";

    killList+=labels[size];

    std::cout << labels[size] <<" Slain!\n";

    delete zombieKilled;
}

void warrior::consumeAmmo(int ammo) {
    warrior::ammo -= ammo;
}

void warrior::takeDamage(int hitPoints) {
    warrior::hitPoints -= hitPoints;
    if (hitPoints<=0)
        alive= false;
}

void warrior::heal(int hitPoints) {
    warrior::hitPoints += hitPoints;
}

void warrior::addAmmo(int amount) {
    ammo+=amount;
}

bool warrior::have2Kills() {
    //checking if 2 zombies are killed
    //if <=1 zombies are killed, then killList has no commas
    //if >=2 zombies are killed, killList has at least 1 comma
    if (killList.find(',')!=std::string::npos){
        //if at least 1 comma found
        return true;
    }
    return false;
}

derick::derick() : warrior('D', 30, DERICK) {}

int derick::shoot() {
    //function to attempt to shoot bullets, returns number of bullets fired
    //returns 2 if 2 bullets fired
    //returns 1 if 1 bullet fired
    //returns 0 if out of ammo
    if (getAmmo() > 1) {
        consumeAmmo(2);
        return 2;
    } else if (getAmmo() == 1){
        consumeAmmo(1);
        return 1;
    } else
        return 0;
}

std::ostream &operator<<(std::ostream &os, const derick &derick) {
    os << "==============================\n"
          "Derick \"Deadeye\" Dreams\n"
          "Green skin is so last season.\n"
          "=============================\n";
    os<< "HP:\t\t"<<derick.getHitPoints()<<"\n";
    os<< "Ammo:\t"<<derick.getAmmo()<<"\n";
    return os;
}

void derick::printOptions() {
    std::cout << "Available Actions: \n";
    std::cout << "[S]hoot\n[K]nife\n";
    std::cout << "How Do You Proceed?\n";
}

int derick::melee() const {
    return 1;
}


chichonne::chichonne() : warrior('C', 25, CHICHONNE), megaKatana(false){}

int chichonne::melee() const {
    if (!megaKatana)
        return 4;
    else
        return 6;
}

int chichonne::shoot() {
    //function to attempt to shoot, and keep track of ammo
    //returns 1 if shooting successful
    //returns 0 if out of bullets
    if (getAmmo()>0) {
        consumeAmmo(1);
        return 1;
    } else
        return 0;
}

void chichonne::addKill(entity *zombieKilled) {
    //overriding to account for keeping track of katana level
    warrior::addKill(zombieKilled);
    if (!megaKatana){
        if (have2Kills()) {
            megaKatana= true;
            std::cout<<"Chichonne's katana has leveled to a Mega Katana!\n";
        }
    }
}

std::ostream &operator<<(std::ostream &os, const chichonne &chichonne) {
    os << "===============================\n"
          "Chichonne \"Crimsonblade\" Mohawk\n"
          "Steel for breakfast,sir?.\n"
          "===============================\n";
    os<< "HP:\t\t"<<chichonne.getHitPoints()<<"\n";
    os<< "Ammo:\t"<<chichonne.getAmmo()<<"\n";
    os<<"Blade level: "<< ((!chichonne.megaKatana)?"Level 1 - Regular katana":"Level 2 - Mega-Katana");
    return os;
}

void chichonne::printOptions() {
    std::cout << "Available Actions: \n";
    std::cout << "[S]hoot\n[K]atana\n";
    std::cout << "How Do You Proceed?\n";
}
