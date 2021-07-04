#ifndef INC_242_ASSIGNMENT_4_GRID_H
#define INC_242_ASSIGNMENT_4_GRID_H

#include <ostream>
#include <vector>
#include "entity.h"
#include "resource.h"
#include "warrior.h"

class grid {
private:
    int size;
    entity*** board;
    bool** visitedByDerek;
    bool** visitedByChichonne;
    int zombiesRemaining;
    bool medkitsDiscovered, zombiesVisible, ammunitionDiscovered;

    //this constant list will return the operations to be done to the x and y coordinates in each direction
    //directions will be done like so
    //  [7]     [0]     [1]
    //  [6]     source  [2]
    //  [5]     [4]     [3]
    const int directionOperations[8][2] = {{-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1}};
public:
    grid(int size);
    int getSize() const;
    entity ***getBoard() const;
    entity* getEntity(int x, int y) const;
    bool allZombiesDead() const;

    bool checkValidMove(warrior *warriorToMove, int targetX, int targetY);
    void move(warrior *warriorToMove, int targetX, int targetY);
    void placeWarriors(warrior* a, warrior* b);
    bool isPlayerTrapped(warrior* player);
    void removeWarriors(warrior* a, warrior* b);

    friend std::ostream &operator<<(std::ostream &os, const grid &grid);
    void debugPrint();

    virtual ~grid();


private:

    void deploy(std::vector<entity *> entitiesToBeAdded);
    entity *removeFromBoard(entity *entityToDelete); //remove an object when you know its coordinates
    std::vector<entity *> createEntities();
    bool checkFree(int sourceX, int sourceY, int direction, int entitySize);
    void placeEntity(int sourceX, int sourceY, int direction, entity *entityPlaced);
    bool coordinatesInRange(int x, int y) const;
};

void printLegend(); //declaration outside scope of class so it is reachable from other files.


#endif //INC_242_ASSIGNMENT_4_GRID_H
