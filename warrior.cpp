
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

    delete zombieKilled;
}

void warrior::consumeAmmo(int ammo) {
    warrior::ammo -= ammo;
}

void warrior::takeDamage(int hitPoints) {
    warrior::hitPoints -= hitPoints;
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

int derick::shootBullets() {
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

chichonne::chichonne() : warrior('C', 25, CHICHONNE), megaKatana(false), katanaKills(0){}

int chichonne::swipeKatana() const {
    if (!megaKatana)
        return 4;
    else
        return 6;
}

bool chichonne::confirmKatanaKill() {
    //keeps track of kills and levels katana
    //returns true if katana levels, false otherwise;

    katanaKills++;
    if (katanaKills>1) {
        megaKatana = true;
        return true;
    }
    return false;
}

int chichonne::shootBullet() {
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
        }
    }
}
