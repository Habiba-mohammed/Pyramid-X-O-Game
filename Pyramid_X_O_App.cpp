
#include <iostream>
#include"BoardGame_Classes.hpp"
#include "Pyramic_Tic_Tac_Toe.h"





using namespace std;

int main() {
    Pyramid_X_O_Board myboard;
    int choice;
    Player * players[2];
    players[0] = new Player (1, 'x');

    cout << "Welcome to FCAI X-O Game. :)\n";
    cout << "Press 1 if you want to play with computer: ";
    cin >> choice;
    if (choice != 1)
        players[1] = new Player (2, '0');
    else
        //Player pointer points to child
        players[1] = new Pyramid_Minimax_Player ('o',myboard);


    GameManager x_o_game (&myboard, players);
    x_o_game.run();
    system ("pause");
}

