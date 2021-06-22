
#ifndef INC_242_ASSIGNMENT_4_TESTPACK_H
#define INC_242_ASSIGNMENT_4_TESTPACK_H

#include "grid.h"
#include "warrior.h"


int adamTest(){
    derick* p = new derick;
    grid b(5);
    int x,y;
    char sep;
    b.debugPrint();

    while(1){
        p->verbosePrint();
        std::cin >> x;
        std::cin>>sep;
        std::cin >> y;
        b.move(p, x, y);
        if (x>=0 && x<b.getSize() && y>=0 && y<b.getSize())
            b.move(p, x, y);
        else
            std::cout<<"error\n";
        b.debugPrint();
    }
    return 0;
};

int ahmedTest(){
    std::cout << "";
    return 0;
}

#endif //INC_242_ASSIGNMENT_4_TESTPACK_H
