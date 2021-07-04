/* Student 1: Adam Mohamed I. K. - 2350775
 * Student 2: Ahmed Mohamed - 2351724
I read and accept the submission rules and the important section specified in assignment file.
This is my own work that is done by myself and my team-mate only */

#include <iostream>
#include "grid.h"
#include "testpack.h"

void printTitle();
void printGameOver();
int initialize(warrior *&player1, warrior *&player2);
void play(warrior* player, grid& board);

int main() {
    // std::cout<< "Bismillah alrahman alrahim\n"; //essential to the correct functioning of this program inshallah
    srand(time(NULL));
    printTitle();
    warrior *player1,*player2;
    grid board = {initialize(player1, player2)};
    bool gameOver=false;
    bool player1Playable = true; //if player is trapped or dead, this is false
    bool player2Playable = true;
    board.placeWarriors(player1,player2); //randomly place warriors on grid
    //above line can be omitted to have players pick their initial locations
    printLegend();
    while(!gameOver){
        std::cout<<board;
        if(player1Playable) {
            std::cout << "===Player 1's turn===\n";
            player1->verbosePrint();
            play(player1, board);
        }
        if (player2Playable) {
            std::cout<<"===Player 2's turn===\n";
            player2->verbosePrint();
            play(player2, board);
        }

        player1Playable = player1->isAlive() && !board.isPlayerTrapped(player1);
        player2Playable = player2->isAlive() && !board.isPlayerTrapped(player2);
        gameOver = board.allZombiesDead() || (!player1Playable && !player2Playable);
    }
    printGameOver();
    player1->verbosePrint();
    player2->verbosePrint();

    board.removeWarriors(player1,player2);
    if (player1->getWarriorType()==DERICK){
        delete (derick*) player1;
        delete (chichonne*) player2;
    }else {
        delete (chichonne*) player1;
        delete (derick*) player2;
    }

    char exit;
    std::cout<<"Thank you for playing! Enter any character to exit: ";
    std::cin>>exit;
    return 0;
}

int initialize(warrior *&player1, warrior *&player2) {
    //initializes given parameters and returns size of board
    int size;
    std::cout<<"Please enter board size( must be at least 5):";
    std::cin >>size;
    while (size < 5){
        std::cout<<"Invalid size, please try again: ";
        std::cin>>size;
    }

    char choice;
    std::cout<<"Player 1: Please select your character:\n"
               "[D]erick Dreams\n"
               "[C]hichonne Mohawk\n";
    std::cin >> choice;
    choice = (char) tolower(choice);
    if (choice!='d' && choice!='c'){//to account for both letter cases
        std::cout<<"Invalid input! Please try again!\n";
        initialize(player1, player2);
    } else if (choice =='d'){
        player1 = new derick;
        player2 = new chichonne;
    } else {
        player1 = new chichonne;
        player2 = new derick;
    }
    return size;
}

void play(warrior* player, grid& board){
    std::cout<<"Please enter target coordinate to move to (in the form x,y): ";
    char sep;
    int x,y;
    std::cin>>x>>sep>>y;
    while(!board.checkValidMove(player, x, y)){
        std::cout<<"Please enter target coordinate to move to (in the form x,y): ";
        std::cin>>x>>sep>>y;
    }

    std::cout<<"\n";
    board.move(player, x, y);
    std::cout << board;
    std::cout<<"\n\n";
}

void printTitle(){
    std::cout<<"\n"
               "█████████████████████████████████████████████████████████████████████████████████\n"
               "█░▄▄░▄█─▄▄─█▄─▀█▀─▄█▄─▄─▀█▄─▄█▄─▄▄─███▄─▄─▀█▄─██─▄█─▄▄▄▄█─▄─▄─█▄─▄▄─█▄─▄▄▀█─▄▄▄▄█\n"
               "██▀▄█▀█─██─██─█▄█─███─▄─▀██─███─▄█▀████─▄─▀██─██─██▄▄▄▄─███─████─▄█▀██─▄─▄█▄▄▄▄─█\n"
               "▀▄▄▄▄▄▀▄▄▄▄▀▄▄▄▀▄▄▄▀▄▄▄▄▀▀▄▄▄▀▄▄▄▄▄▀▀▀▄▄▄▄▀▀▀▄▄▄▄▀▀▄▄▄▄▄▀▀▄▄▄▀▀▄▄▄▄▄▀▄▄▀▄▄▀▄▄▄▄▄▀\n\n";
}

void printGameOver(){
    std::cout<<"\n"
               "█████▀██████████████████████████████████████████████\n"
               "█─▄▄▄▄██▀▄─██▄─▀█▀─▄█▄─▄▄─███─▄▄─█▄─█─▄█▄─▄▄─█▄─▄▄▀█\n"
               "█─██▄─██─▀─███─█▄█─███─▄█▀███─██─██▄▀▄███─▄█▀██─▄─▄█\n"
               "▀▄▄▄▄▄▀▄▄▀▄▄▀▄▄▄▀▄▄▄▀▄▄▄▄▄▀▀▀▄▄▄▄▀▀▀▄▀▀▀▄▄▄▄▄▀▄▄▀▄▄▀\n";
}