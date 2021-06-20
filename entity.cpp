#include "entity.h"

char entity::getRepresentingChar() const {
    return representingChar;
}

int entity::getSize() const {
    return size;
}

entity::entity(int size, char representingChar) : size(size), representingChar(representingChar) {}
