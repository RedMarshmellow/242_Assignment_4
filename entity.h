#ifndef INC_242_ASSIGNMENT_4_ENTITY_H
#define INC_242_ASSIGNMENT_4_ENTITY_H

//ammunition and medkit classes combined here since they are pretty small

#include <ostream>

class entity {
private:
    int size;
    char representingChar;
protected:
    void setRepresentingChar(char representingChar); //only want subclasses to acces this
public:
    friend std::ostream &operator<<(std::ostream &os, const entity &entity);
    entity(int size, char representingChar);
    entity(int size);

    char getRepresentingChar() const;

    int getSize() const;
};


class resource: public entity{
public:
    resource(int size, char representingChar);
};

class ammunition : public resource {
public:
    ammunition() : resource(1, 'A') {}
};

class medkit: public resource{
public:
    medkit(int size) : resource(size, (size==1)?'+':'*') {}
};

#endif //INC_242_ASSIGNMENT_4_ENTITY_H