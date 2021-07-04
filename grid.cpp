#include "grid.h"
#include <math.h>
#include <vector>
#include "zombie.h"
#include <iostream>
#include "battlesystem.h"
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
            if (board[i][j] != nullptr && board[i][j]->getEntityType()!=Warrior)
                entitiesToDelete.insert(board[i][j]);
        }
        delete[] board[i];
    }
    delete[] board;

    for (int i = 0; i < size; ++i) {
        delete[] visitedByChichonne[i];
        delete[] visitedByDerek[i];
    }
    delete[] visitedByChichonne;
    delete[] visitedByDerek;

    //iterate through unique set, deleting each entity
    for (std::set<entity*>::iterator i = entitiesToDelete.begin(); i != entitiesToDelete.end(); ++i) {
        //deleting and iterating
        delete *i;
    }
}

grid::grid(int size) : size(size),zombiesVisible(false), medkitsDiscovered(false), ammunitionDiscovered(false) {
    board = new entity **[size];
    for (int i = 0; i < size; ++i) {
        board[i] = new entity *[size];
        for (int j = 0; j < size; ++j) {
            board[i][j] = nullptr;
        }
    }

    visitedByChichonne = new bool*[size];
    visitedByDerek = new bool*[size];
    for (int i = 0; i < size; ++i) {
        visitedByChichonne[i] = new bool[size];
        visitedByDerek[i] = new bool[size];
        for (int j = 0; j < size; ++j) {
            visitedByChichonne[i][j] = false;
            visitedByDerek[i][j] = false;
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

std::vector<entity *> grid::createEntities() {
    int numberOfZombiesAndAmmo = 2 * (int) floor(size * size / 25);
    int numberOfMedkits = 3 * (int) floor(size * size / 25);

    zombiesRemaining = numberOfZombiesAndAmmo;

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
            entitySize = rand() % 2;
            while (!availableSizes[entitySize]) {
                entitySize = rand() % 2;
            }
        } else{
            entitySize = rand() % 2;
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


    int entitySize = entityPlaced->getSize();
    for (int i = 0; i < entitySize; ++i) {
        board[x][y] = entityPlaced;
        x+=directionOperations[direction][0];
        y+=directionOperations[direction][1];
    }
    entityPlaced->setLocation(sourceX,sourceY,direction);
}

std::ostream &operator<<(std::ostream &os, const grid &grid) {
    os<<"X  | Y\t";
    for (int i = 0; i < grid.getSize(); ++i) {
        //displaying indexes at top
        os<< i <<"\t\t";
    }
    os<<"\n";
    for (int i = 0; i < grid.getSize(); ++i) {
        //the number of equals here is based on trial and error in my environment
        os<< "==========";
    }
    os<<"\n";
    entity*** board = grid.getBoard();
    for (int i = 0; i < grid.getSize(); ++i) {
        os<< i << "  |\t";
        for (int j = 0; j < grid.getSize(); ++j) {

            bool visible= true; //invisible will represent both undiscovered and also empty tiles of the board
            if (board[i][j] == nullptr) visible = false;
            else {
                entityTypes type = board[i][j]->getEntityType();
                if (type == Resource) {
                    resourceTypes rType = ((resource *) board[i][j])->getResourceType();
                    if (rType==Ammo)
                        visible = grid.ammunitionDiscovered;
                    if (rType==Health)
                            visible = grid.medkitsDiscovered;
                }
                else if (type==Zombie)
                    visible = grid.zombiesVisible; //usually invisible, but can be visible for debugging
            }

            if (visible)
                os << *board[i][j];
            else {
                //if not visible may be visited before so check for that
                char charToPrint='_';
                if (grid.visitedByDerek[i][j])
                    charToPrint = 'X';
                if (grid.visitedByChichonne[i][j]){
                    if (charToPrint=='_')
                        charToPrint='#';
                    else
                        charToPrint='&';
                }
                os << charToPrint; }
            os<<"\t\t";
        }
        os<<"\n";
    }
    return os;
}

void grid::move(warrior *warriorToMove, int targetX, int targetY) {
    //main function to move players around the board.
    if (!checkValidMove(warriorToMove, targetX, targetY))
        //redundant check since validity is checked outside, but just in case
        return;

    //if move is valid, begin move by removing old warrior from board
    if (warriorToMove->getSourceX()!=-1)
        removeFromBoard(warriorToMove);
        if (board[targetX][targetY]!= nullptr) {
            if (board[targetX][targetY]->getEntityType() == Zombie) {
            int outcome = battle(warriorToMove,(zombie*) board[targetX][targetY]);
            if (outcome==1){
                //if player loses
                return;
            } else {
                entity* zombieToDelete = removeFromBoard(board[targetX][targetY]);
                delete zombieToDelete;
                zombiesRemaining--;
            }
        } else{
            //if resource, consume it
            warriorToMove->consumeResource((resource *) board[targetX][targetY]);
            resource* resourceToDelete = (resource *) removeFromBoard(board[targetX][targetY]);
            resourceTypes type =resourceToDelete->getResourceType();
            delete resourceToDelete;
            if (type==Ammo){
                ammunitionDiscovered= true;
            } else{
                medkitsDiscovered = true;
            }
        }
    }

    board[targetX][targetY] = warriorToMove;
    warriorToMove->setLocation(targetX,targetY,0);
    if (warriorToMove->getWarriorType()==DERICK){
        visitedByDerek[targetX][targetY]= true;
    }if (warriorToMove->getWarriorType()==CHICHONNE){
        visitedByChichonne[targetX][targetY]= true;
    }
}

bool grid::checkValidMove(warrior *warriorToMove, int targetX, int targetY) {

    if (!coordinatesInRange(targetX,targetY))
        return false;


    if (warriorToMove->getX() == -1){
        //if this is the first move, just check for board boundaries
        return true;
    }

    if (warriorToMove->getX()==targetX && warriorToMove->getY()==targetY) {
        std::cout<<"You're already there!\n";
        return false;
    }

    if (board[targetX][targetY] != nullptr && board[targetX][targetY]->getEntityType() == Warrior) {
        std::cout << "Can't move to another warrior's space!\n";
        return false;
    }

    if (warriorToMove->getWarriorType()==DERICK && visitedByDerek[targetX][targetY] ||
    warriorToMove->getWarriorType()==CHICHONNE && visitedByChichonne[targetX][targetY]){
        std::cout<< "Tile previously visited!\n";
        return false;
    }

    //check for adjacency by comparing to current location of warrior
    int differenceX= abs(warriorToMove->getX()-targetX);
    int differenceY= abs(warriorToMove->getY()-targetY);
    if (differenceY<=1 && differenceX<= 1)
        return true;
    else{
        std::cout<<"Can't move to non-adjacent tile!\n";
        return false;
    }
}

entity *grid::removeFromBoard(entity *entityToDelete) {

    int x= entityToDelete->getSourceX();
    int y = entityToDelete->getSourceY();
    int direction = entityToDelete->getDirection();
    for (int i = 0; i < entityToDelete->getSize(); ++i) {
        board[x][y] = nullptr;
        x += directionOperations[direction][0];
        y += directionOperations[direction][1];
    }

    return entityToDelete;
}

void grid::debugPrint() {
    bool a=ammunitionDiscovered,z=zombiesVisible,m=medkitsDiscovered;
    ammunitionDiscovered= true,zombiesVisible = true, medkitsDiscovered= true;
    std::cout << *this;
    ammunitionDiscovered= a,zombiesVisible = z, medkitsDiscovered= m;
}

void grid::placeWarriors(warrior *a, warrior *b) {
    //function to randomly place the warriors in an empty tile on the grid
    int x = rand() % size;
    int y = rand() % size;
    while (board[x][y]!= nullptr){
        x = rand() % size;
        y = rand() % size;
    }
    move(a,x,y);
    while(board[x][y]!= nullptr){
        x = rand() % size;
        y = rand() % size;
    }
    move(b,x,y);

}

bool grid::allZombiesDead() const {
    return zombiesRemaining <= 0;
}

bool grid::isPlayerTrapped(warrior *player) {
    int playerX = player->getX();
    int playerY = player->getY();
    bool** visited;
    if (player->getWarriorType()==DERICK)
        visited= visitedByDerek;
    else
        visited=visitedByChichonne;
    for (int i = 0; i < 8; ++i) {
        int x,y;
        x= playerX + directionOperations[i][0];
        y= playerY + directionOperations[i][1];
        if (coordinatesInRange(x, y) && !visited[x][y])
            return false;
    }

    std::cout<<"Uh oh! "<< ((player->getWarriorType() == DERICK)?"Derick ":"Chichonne ") << "is trapped and cannot move!\nThey are eliminated from the game!\n";
    return true;
}

bool grid::coordinatesInRange(int x, int y) const {
    //function to check if coordinates are valid
    return (x >= 0 && x < size && y >= 0 && y < size);
}

bool grid::removeWarriors(warrior *a, warrior *b) {
    //the pointers to the warriors must be removed from the board before destruction so we don't double delete
    removeFromBoard(a);
    removeFromBoard(b);
}

void printLegend() {
    //this was going to be in a separate .txt file but that introduced unnecessary issues
    std::cout<<"========================================\n"
               "Legend:\n"
               "[A] Ammunition      [L] Large Zombie\n"
               "[+] Small Medkit    [M] Medium Zombie\n"
               "[*] Large Medkit    [S] Small Zombie\n"
               "[D] Derick Dreams   [C] Chichonne Mohawk\n"
               "[X] Coordinate visited by Derek\n"
               "[#] Coordinate visited by Chichonne\n"
               "[&] Coordinate visited by both warriors\n"
               "========================================\n\n";
}
