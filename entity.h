#ifndef INC_242_ASSIGNMENT_4_ENTITY_H
#define INC_242_ASSIGNMENT_4_ENTITY_H

//ammunition and medkit classes combined here since they are pretty small

#include <ostream>
enum entityTypes{Warrior,Resource,Zombie};
class entity {
private:
    entityTypes type;
    int size;
    char representingChar;
protected:
    void setRepresentingChar(char representingChar); //only want subclasses to access this
public:
    friend std::ostream &operator<<(std::ostream &os, const entity &entity);
    entity(int size, char representingChar, entityTypes type);
    entity(int size);

    char getRepresentingChar() const;

    entityTypes getType() const;

    int getSize() const;
};

#endif //INC_242_ASSIGNMENT_4_ENTITY_H