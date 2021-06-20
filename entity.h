#ifndef INC_242_ASSIGNMENT_4_ENTITY_H
#define INC_242_ASSIGNMENT_4_ENTITY_H


class entity {
private:
    int size;
    char representingChar;
public:
    entity(int size, char representingChar);

    char getRepresentingChar() const;
    int getSize() const;
};


#endif //INC_242_ASSIGNMENT_4_ENTITY_H
