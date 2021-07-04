
#include <iostream>
#include "warrior.h"

warrior::warrior(char representingChar, int ammo, enum warriorTypes warriorType) : warriorType(warriorType),
                                                                                   entity(1, representingChar, Warrior),
                                                                                   hitPoints(1), ammo(ammo), score(0),
                                                                                   alive(true) {
    setLocation(-1, -1, 0);
}


void warrior::addScore(int addition) {
    score += addition;
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

const std::string &warrior::getKillList() const {
    return killList;
}

void warrior::addKill(entity *zombieKilled) {
    //function to automatically update score and killList from zombie entity
    //also will keep track of katana Leveling
    //note: as of writing, the function will also delete zombie object, may change later

    int size = zombieKilled->getSize() - 1;
    int scores[3] = {50, 75, 100};
    addScore(scores[size]);

    std::string labels[3] = {"Small Zombie", "Medium Zombie", "Large Zombie"};
    if (!killList.empty())
        killList += ",";

    killList += labels[size];

    std::cout << labels[size] << " Slain!\n";
}

void warrior::consumeAmmo(int ammo) {
    warrior::ammo -= ammo;
}

void warrior::takeDamage(int damage) {
    hitPoints -= damage;
    if (hitPoints <= 0) {
        alive = false;
        hitPoints=0;
    }
}

void warrior::heal(int hitPoints) {
    warrior::hitPoints += hitPoints;
}

void warrior::addAmmo(int amount) {
    ammo += amount;
}

bool warrior::have2Kills() {
    //checking if 2 zombies are killed
    //if <=1 zombies are killed, then killList has no commas
    //if >=2 zombies are killed, killList has at least 1 comma
    if (killList.find(',') != std::string::npos) {
        //if at least 1 comma found
        return true;
    }
    return false;
}

void warrior::consumeResource(resource *resourceToConsume) {
    if (resourceToConsume->getResourceType() == Ammo) {
        addAmmo(resourceToConsume->resupply());
    } else {
        heal(resourceToConsume->resupply());
    }

    std::cout << ((warriorType == DERICK) ? "Derick" : "Chichonne") << " found a"
              << ((resourceToConsume->getResourceType() == Ammo) ? "n ammunition box" : " medicine kit") << "!\n";

}

warriorTypes warrior::getWarriorType() const {
    return warriorType;
}

int warrior::getX() const {
    return getSourceX();
}

int warrior::getY() const {
    return getSourceY();
}

derick::derick() : warrior('D', 30, DERICK) {}

int derick::shoot() {
    //function to attempt to shoot bullets, returns number of bullets fired
    //returns 2 if 2 bullets fired
    //returns 1 if 1 bullet fired
    //returns 0 if out of ammo
    if (getAmmo() > 1) {
        consumeAmmo(2);
        std::cout << "Two Shots Are Fired!\n";
        return 2;
    } else if (getAmmo() == 1) {
        consumeAmmo(1);
        std::cout << "One Shot Is Fired!\n";
        return 1;
    } else
        std::cout << "The Hammer Falls..........But No Shots Are Heard, Out of Ammo!\n";
        return 0;
}

void derick::printOptions() {
    std::cout << "Available Actions: \n";
    std::cout << "[S]hoot\n[K]nife\n";
    std::cout << "How Do You Proceed?\n";
}

int derick::melee() const {
    return 1;
}

void derick::verbosePrint() {
    std::cout << "======================\n"
                 "Derick \"Deadeye\"Dreams\n"
                 "======================\n";
    std::cout << "HP:\t\t" << getHitPoints() << "\n";
    std::cout << "Ammo:\t" << getAmmo() << "\n";
    std::cout << "Score:\t" << getScore() << "\n";
    if (!getKillList().empty())std::cout << "Derick has killed: " << getKillList() << "\n";
}



chichonne::chichonne() : warrior('C', 25, CHICHONNE), megaKatana(false) {}

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
    if (getAmmo() > 0) {
        consumeAmmo(1);
        std::cout << "A Bullet Races Out of the Pistol's Barrel!\n";
        return 1;
    } else
        std::cout << "A Loud 'Click!' Rings Out of the Pistol, Out of Ammo!\n";
        return 0;
}

void chichonne::addKill(entity *zombieKilled) {
    //overriding to account for keeping track of katana level
    warrior::addKill(zombieKilled);
    if (!megaKatana) {
        if (have2Kills()) {
            megaKatana = true;
            std::cout << "Chichonne's katana has leveled to a Mega Katana!\n";
        }
    }
}

void chichonne::printOptions() {
    std::cout << "Available Actions: \n";
    std::cout << "[S]hoot\n[K]atana\n";
    std::cout << "How Do You Proceed?\n";
}

void chichonne::verbosePrint() {
    std::cout << "===============================\n"
                 "Chichonne \"Crimsonblade\" Mohawk\n"
                 "===============================\n";
    std::cout << "HP:\t\t" << getHitPoints() << "\n";
    std::cout << "Ammo:\t" << getAmmo() << "\n";
    std::cout << "Score:\t" << getScore() << "\n";
    std::cout << "Blade level: " << ((!megaKatana) ? "Level 1 - Regular katana" : "Level 2 - Mega-Katana")<<"\n";
    if (!getKillList().empty()) std::cout << "Chichonne has killed: " << getKillList() << "\n";
}

