
#ifndef INC_242_ASSIGNMENT_4_TESTPACK_H
#define INC_242_ASSIGNMENT_4_TESTPACK_H

#include "grid.h"
#include "warrior.h"
#include "battlesystem.h"
#include "iostream"

void printEvent(std::string event){
    int len = event.length()+4;
    std::cout<<"+";
    for (int i = 0; i < len; ++i) {
        std::cout<<"-";
    }
    std::cout<<"+\n";
    std::cout<<"|! "<<event<<" !|\n";
    std::cout<<"+";
    for (int i = 0; i < len; ++i) {
        std::cout<<"-";
    }
    std::cout<<"+"<<std::endl;
}

class A{
    public:
    int x=5;
    virtual void print() {
        std::cout<<x<<std::endl;
    }
};

class B: virtual public A{
public:
    int y=6;

    void print()override{
        std::cout<<y<<std::endl;
    }
};


int adamTest() {
    derick *p = new derick;
    chichonne *p2 = new chichonne;
    grid b(5);
    b.placeWarriors(p,p2);
    int x, y;
    char sep;
    std::cout<<b;

    while (1) {
        p->verbosePrint();
        std::cin >> x;
        std::cin >> sep;
        std::cin >> y;
        if (x >= 0 && x < b.getSize() && y >= 0 && y < b.getSize())
            b.move(p, x, y);
        else
            std::cout << "error\n";
        std::cout << b;
    }
    return 0;
};

int ahmedTest() {
    zombie *z = new zombie(3);
    derick *p = new derick;
    int test = battle(p, z);
    return 0;
}

#endif //INC_242_ASSIGNMENT_4_TESTPACK_H
