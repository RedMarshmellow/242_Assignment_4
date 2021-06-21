#ifndef INC_242_ASSIGNMENT_4_GRID_H
#define INC_242_ASSIGNMENT_4_GRID_H

#include <ostream>
#include <vector>
#include "entity.h"

class grid {
private:
    int size;
    entity*** board;
public:
    grid(int size);

    int getSize() const;
    entity ***getBoard() const;
    entity* getEntity(int x, int y) const;

    bool checkFree(int sourceX, int sourceY, int direction, int entitySize);
    void placeEntity(int sourceX, int sourceY, int direction, entity *entityPlaced);

    friend std::ostream &operator<<(std::ostream &os, const grid &grid);
    virtual ~grid();

    void deploy(std::vector<entity *> entitiesToBeAdded);

    std::vector<entity *> createEntities() const;
};


#endif //INC_242_ASSIGNMENT_4_GRID_H
