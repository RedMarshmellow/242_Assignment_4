#ifndef INC_242_ASSIGNMENT_4_GRID_H
#define INC_242_ASSIGNMENT_4_GRID_H
#include "entity.h"

class grid {
private:
    int size;
    entity*** board;
public:
    grid(int size);

    int getSize() const;
    entity ***getBoard() const;

    virtual ~grid();
};


#endif //INC_242_ASSIGNMENT_4_GRID_H
