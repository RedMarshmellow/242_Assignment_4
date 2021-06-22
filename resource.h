#ifndef INC_242_ASSIGNMENT_4_RESOURCE_H
#define INC_242_ASSIGNMENT_4_RESOURCE_H
#include "entity.h"

enum resourceTypes{Ammo,Health};

class resource : public entity {
private:
    int replenish;
protected:
     resourceTypes type;
public:
    resource(int size, char representingChar, int replenish, resourceTypes type);

public:
    resourceTypes getType() const;

    int resupply();
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
