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

grid::grid(int size) : size(size),zombiesDiscovered(false),medkitsDiscovered(false),ammunitionDiscovered(false) {
    board = new entity **[size];
    for (int i = 0; i < size; ++i) {
        board[i] = new entity *[size];
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


    int entitySize = entityPlaced->getSize();
    for (int i = 0; i < entitySize; ++i) {
        board[x][y] = entityPlaced;
        x+=directionOperations[direction][0];
        y+=directionOperations[direction][1];
    }
    entityPlaced->setLocation(sourceX,sourceY,direction);
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

            bool visible=true; //invisible will represent both undiscovered and also empty tiles of the board
            if (board[i][j] == nullptr) visible = false;
            else {
                char type = board[i][j]->getRepresentingChar();
                if (type == '+' || type == '*')
                    visible = grid.medkitsDiscovered;
                else if (type == 'S' || type == 'M' || type == 'L')
                    visible = grid.zombiesDiscovered;
                else if (type=='A')
                    visible = grid.ammunitionDiscovered;
            }

            if (visible)os << *board[i][j];
            else { os << "_"; }
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
    if (board[targetX][targetY]== nullptr) {
        board[targetX][targetY] = warriorToMove;
    }else if (board[targetX][targetY]->getType() == Zombie) {
        int outcome = battle(warriorToMove,(zombie*) board[targetX][targetY]);
        if (outcome==1){
            //if player loses
            return;
        } else {
            entity* zombieToDelete = removeFromBoard(board[targetX][targetY]);
            delete zombieToDelete;
            board[targetX][targetY]=warriorToMove;
        }
    } else{
        //if resource, consume it
        warriorToMove->consumeResource((resource *) board[targetX][targetY]);
        entity* resourceToDelete = removeFromBoard(board[targetX][targetY]);
        delete resourceToDelete;
        board[targetX][targetY] = warriorToMove;
    }

    warriorToMove->setLocation(targetX,targetY,0);
}

bool grid::checkValidMove(warrior *warriorToMove, int targetX, int targetY) {
    //if a player wants to move to a coordinate, they have to be adjacent to it
    if (warriorToMove->getX() == -1){
        //if this is the first move, just check for board boundaries
        if (targetX>=0 && targetX<size && targetY>=0 && targetY<size)
            return true;
    }

    if (warriorToMove->getY()==targetX && warriorToMove->getY()==targetY) {
        std::cout<<"You're already there!\n";
        return false;
    }

    if (board[targetX][targetY] != nullptr && board[targetX][targetY]->getType()==Warrior) {
        std::cout << "Can't move to another warrior's space!\n";
        return false;
    }

    //check for adjacency by comparing to current location of warrior
    int differenceX= abs(warriorToMove->getX()-targetX);
    int differenceY= abs(warriorToMove->getY()-targetY);
    if (differenceY<=1 && differenceX<= 1)
        return true;

    return false;
}

entity *grid::removeFromBoard(entity *entityToDelete) {
    //function to remove an entity from the board
    //if object's size >1, the function finds the direction the object is deployed in
    //then uses that to remove it from the board;

//    board[locationX][locationY] = nullptr;
//    if (entityToDelete->getSize()==1)
//        return entityToDelete;
//    else{
//        //first find direction
//        bool foundDirection= false;
//        int direction=0;
//        for (int x = locationX, y = locationY;
//         direction < 8 && !foundDirection; //loop terminates until direction of object is found
//        ++direction) {
//
//            if (x >= 0 && x < size && y >= 0 && y < size &&
//            board[x][y]==entityToDelete) {
//                //once object is found, remove it
//                board[x][y] = nullptr;
//                foundDirection = true;
//            }
//            else {
//                x = locationX + directionOperations[direction][0];
//                y = locationY + directionOperations[direction][1];
//            }
//        }
//
//        if (entityToDelete->getSize() == 3) {
//            //if entity is size 3, that means we could have encountered the middle of it
//            //thus we need to check if the original encountered location has another adjacent duplicate
//
//            bool foundAnotherDuplicate= false;
//            for (int localDir = direction + 1, x = locationX, y = locationY;
//                localDir < 8 && !foundAnotherDuplicate;
//                ++localDir) {
//
//                //create sourceDir so as not to overwrite previously found direction
//                //perform search right after prevously found direction so as to find if there are other duplicates
//                if (x >= 0 && x < size && y >= 0 && y < size &&
//                    board[x][y] == entityToDelete) {
//
//                    //once object is found, remove it
//                    board[x][y] = nullptr;
//                    foundAnotherDuplicate = true;
//                } else {
//                    x = locationX += directionOperations[direction][0];
//                    y = locationY += directionOperations[direction][1];
//                }
//            }
//
//            if (!foundAnotherDuplicate){
//                //if earlier loop did not find a duplicate that means we didnt encounter the middle of the entity
//                //and just need to continue in the previously found direction
//                int x= locationX + 2* directionOperations[direction][0];
//                int y = locationY + 2* directionOperations[direction][1];
//                board[x][y] = nullptr;
//            }
//        }
//
//    }

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
    bool a=ammunitionDiscovered,z=zombiesDiscovered,m=medkitsDiscovered;
    ammunitionDiscovered= true,zombiesDiscovered = true, medkitsDiscovered= true;
    std::cout << *this;
    ammunitionDiscovered= a,zombiesDiscovered = z, medkitsDiscovered= m;
}

void printLegend() {
    //this was going to be in a separate .txt file but that introduced unnecessary issues
    std::cout<<"========================================\n"
               "Legend:\n"
               "[A] Ammunition      [L] Large Zombie\n"
               "[+] Small Medkit    [M] Medium Zombie\n"
               "[*] Large Medkit    [S] Small Zombie\n"
               "[D] Derick Dreams   [C] Chichonne Mohawk\n"
               "========================================\n";
}
