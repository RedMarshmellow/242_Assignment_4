#include "entity.h"

char entity::getRepresentingChar() const {
    return representingChar;
}

int entity::getSize() const {
    return size;
}

entity::entity(int size, char representingChar) : size(size), representingChar(representingChar) {}

// _ to be used as a sentinel representing char to be replaced
entity::entity(int size) : size(size),representingChar('_') {}

void entity::setRepresentingChar(char representingChar) {
    entity::representingChar = representingChar;
}

std::ostream &operator<<(std::ostream &os, const entity &entity) {
    os << entity.representingChar;
    return os;
}
