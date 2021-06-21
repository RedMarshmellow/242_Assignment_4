#ifndef INC_242_ASSIGNMENT_4_RESOURCE_H
#define INC_242_ASSIGNMENT_4_RESOURCE_H

#include "entity.h"

class resource : public entity {
private:
    int replenish;
protected:
    enum Types{Ammo,Health} type;
public:
    resource(int size, char representingChar, int replenish, Types type);

public:

    int Resupply();
};


class medkit : public resource{

private:
    enum Sizes{S,L} size;
public:
    medkit(int size);
    Sizes returnsize();
};

class ammunition : public resource{
public:
    ammunition();
};

#endif //INC_242_ASSIGNMENT_4_RESOURCE_H
