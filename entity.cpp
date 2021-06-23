#include "entity.h"
char entity::getRepresentingChar() const {
    return representingChar;
}

int entity::getSize() const {
    return size;
}

entity::entity(int size, char representingChar, entityTypes type) : size(size), representingChar(representingChar), type(type) {}

// _ to be used as a sentinel representing char to be replaced
entity::entity(int size) : size(size),representingChar('_') {}

void entity::setRepresentingChar(char representingChar) {
    entity::representingChar = representingChar;
}

std::ostream &operator<<(std::ostream &os, const entity &entity) {
    os << entity.representingChar;
    return os;
}

entityTypes entity::getType() const {
    return type;
}

void entity::setLocation(int x, int y, int direction){
    sourceX=x;
    sourceY=y;
    entity::direction = direction;
}

int entity::getSourceX() const {
    return sourceX;
}

int entity::getSourceY() const {
    return sourceY;
}

int entity::getDirection() const {
    return direction;
}
