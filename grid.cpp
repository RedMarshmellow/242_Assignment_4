#include "grid.h"
#include <math.h>
#include <vector>
#include "zombie.h"
#include <iostream>
#include <set> //i need this for just 1 operation in the destructor

int grid::getSize() const {
    return size;
}

entity ***grid::getBoard() const {
    return board;
}

grid::~grid() {
    //to avoid duplicate deletion, we will add all our unique entities to this set here, then delete them
    std::set<entity*> entitiesToDelete;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (board[i][j] != nullptr) entitiesToDelete.insert(board[i][j]);
        }
        delete[] board[i];
    }
    delete[] board;
    //iterate through unique set, deleting each entity
    for (std::set<entity*>::iterator i = entitiesToDelete.begin(); i != entitiesToDelete.end(); ++i) {
        //deleting and iterating
        delete *i;
    }
}

grid::grid(int size) : size(size) {
    board = new entity**[size];
    for (int i = 0; i < size; ++i) {
        board[i] = new entity*[size];
        for (int j = 0; j < size; ++j) {
            board[i][j] = nullptr;
        }
    }
    std::vector<entity *> entitiesToBeAdded = createEntities();
    deploy(entitiesToBeAdded);
}

void grid::deploy(std::vector<entity *> entitiesToBeAdded) {

    //deciding directions will be done like so
    //  [7]     [0]     [1]
    //  [6]     source  [2]
    //  [5]     [4]     [3]

    int entityNum = (int) entitiesToBeAdded.size();
    for (int i = 0; i < entityNum; ++i) {
        entity* entityToBeInserted = entitiesToBeAdded[i];
        int direction = rand()%8;
        int x=rand()%size;
        int y=rand()%size;
        int entitySize = entityToBeInserted->getSize();
        while (!checkFree(x, y, direction, entitySize)){
            direction = rand()%8;
            x=rand()%size;
            y=rand()%size;
        }
        placeEntity(x, y, direction, entityToBeInserted);
    }
}

std::vector<entity *> grid::createEntities() const {
    int numberOfZombiesAndAmmo = 2 * (int) floor(size * size / 25);
    int numberOfMedkits = 3 * (int) floor(size * size / 25);

    //simple vector so as not to deal with dynamic allocation
    std::vector <entity*> entitiesToBeAdded;

    bool availableSizes[3] = {true,true,true};
    bool allSizesDeployed=false;
    const char labels[3]={'S','M','L'};
    for (int i = 0; i < numberOfZombiesAndAmmo; ++i) {
        int entitySize;
        if (!allSizesDeployed){
            //first generate 1 zombie of each size, and if that's done,
            //to add randomness just rand without care for balance
            entitySize = rand() % 3;
            while (!availableSizes[entitySize]) {
                entitySize = rand() % 3;
            }
        } else{
            entitySize = rand() % 3;
        }
        zombie* zombieToInsert = new zombie {entitySize + 1};
        entitiesToBeAdded.push_back(zombieToInsert);
        ammunition*  ammunitionToInsert = new ammunition;
        entitiesToBeAdded.push_back(ammunitionToInsert);

        //could use a counter alongside array so as not to check it each loop but it's only 3 bytes
        if (availableSizes[0] == availableSizes[1] && availableSizes[1] == availableSizes[2] && availableSizes[2]== false){
            allSizesDeployed = true;
        }
    }

    //reusing available sizes array
    availableSizes[0] = true;
    availableSizes[1] = true;
    allSizesDeployed= false;
    for (int i = 0; i < numberOfMedkits; ++i) {
        int entitySize;
        if (!allSizesDeployed){
            entitySize = rand() % 3;
            while (!availableSizes[entitySize]) {
                entitySize = rand() % 3;
            }
        } else{
            entitySize = rand() % 3;
        }
        availableSizes[entitySize] = false;
        medkit *medkitToBeAdded = new medkit(entitySize + 1);
        entitiesToBeAdded.push_back(medkitToBeAdded);

        if(availableSizes[0]==availableSizes[1] && availableSizes[1]==false){
            allSizesDeployed = true;
        }
    }
    return entitiesToBeAdded;
}

entity *grid::getEntity(int x, int y) const {
    return board[x][y];
}

bool grid::checkFree(int sourceX, int sourceY, int direction, int entitySize) {
    //again directions will be done like so
    //  [7]     [0]     [1]
    //  [6]     source  [2]
    //  [5]     [4]     [3]

    int x = sourceX,y=sourceY;

    //this constant list will return the operations to be done to the x and y coordinates in each direction
    const int directionOperations[8][2] = {{-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1}};
    for (int i = 0; i < entitySize; ++i) {
        if (x>=size||y>=size||x<0||y<0)
            return false;
        if (board[x][y]!= nullptr)
            return false;
        x+=directionOperations[direction][0];
        y+=directionOperations[direction][1];
    }
    return true;
}

void grid::placeEntity(int sourceX, int sourceY, int direction, entity *entityPlaced) {
    //again directions will be done like so
    //  [7]     [0]     [1]
    //  [6]     source  [2]
    //  [5]     [4]     [3]

    int x = sourceX,y=sourceY;

    //this constant list will return the operations to be done to the x and y coordinates in each direction
    const int directionOperations[8][2] = {{-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1}};
    int entitySize = entityPlaced->getSize();
    for (int i = 0; i < entitySize; ++i) {
        board[x][y] = entityPlaced;
        x+=directionOperations[direction][0];
        y+=directionOperations[direction][1];
    }
}

std::ostream &operator<<(std::ostream &os, const grid &grid) {
    os<<"\t\t";
    for (int i = 0; i < grid.getSize(); ++i) {
        //displaying indexes at stop
        os<< i <<"\t\t";
    }
    os<<"\n";
    for (int i = 0; i < grid.getSize(); ++i) {
        //this is implementation dependent so the number of equals here is just trial and error in my environment
        os<< "==========";
    }
    os<<"\n";
    entity*** board = grid.getBoard();
    for (int i = 0; i < grid.getSize(); ++i) {
        os<< i << "  |\t";
        for (int j = 0; j < grid.getSize(); ++j) {
            if (board[i][j]!= nullptr)os<< *board[i][j];
            else os<< "_";
            os<<"\t\t";
        }
        os<<"\n";
    }
    return os;
}
