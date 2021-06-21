#ifndef INC_242_ASSIGNMENT_4_ENTITY_H
#define INC_242_ASSIGNMENT_4_ENTITY_H

//ammunition and medkit classes combined here since they are pretty small

#include <ostream>

class entity {
private:
    int size;
    char representingChar;
protected:
    void setRepresentingChar(char representingChar); //only want subclasses to access this
public:
    friend std::ostream &operator<<(std::ostream &os, const entity &entity);
    entity(int size, char representingChar);
    entity(int size);

    char getRepresentingChar() const;

    int getSize() const;


};
//class ammunition : public entity {
//public:
//    ammunition() : entity(1, 'A') {}
//};
//
//class medkit: public entity{
//public:
//    medkit(int size) : entity(size, (size==1)?'+':'*') {}
//};

#endif //INC_242_ASSIGNMENT_4_ENTITY_H