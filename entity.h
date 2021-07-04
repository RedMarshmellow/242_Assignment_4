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
    int sourceX, sourceY, direction; //this information tells us how the entity is stored and the board and helps in deleting it
protected:
    void setRepresentingChar(char representingChar); //only want subclasses to access this
public:

    entity(int size, char representingChar, entityTypes type);
    entity(int size);

    friend std::ostream &operator<<(std::ostream &os, const entity &entity);
    char getRepresentingChar() const;
    entityTypes getEntityType() const;
    int getSize() const;

    void setLocation(int x, int y, int direction);

    int getSourceX() const;

    int getSourceY() const;

    int getDirection() const;
};

#endif //INC_242_ASSIGNMENT_4_ENTITY_H