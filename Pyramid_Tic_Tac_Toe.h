

//
// Created by Dell on 12/17/2023.
//

#ifndef SRC_PYRAMIC_TIC_TAC_TOE_H
#define SRC_PYRAMIC_TIC_TAC_TOE_H

#include"BoardGame_Classes.hpp"

class Pyramid_X_O_Board:public Board {
public:
    Pyramid_X_O_Board();
    bool update_board (int x, int y, char mark);
    void display_board();
    bool is_winner();
    bool is_draw();
    bool game_is_over();
    bool is_zero(int&i,int&j){
        return board[i][j]==0;
    };

    void undo(int&i,int&j){
        n_moves--;
        board[i][j]=0;
    };

    int is_winner_minmax();


};


class Pyramid_Minimax_Player : public Player {
public:
    Pyramid_Minimax_Player(char symbol,Pyramid_X_O_Board& board);
    void get_move(int & x, int&y);
    int minimax(Pyramid_X_O_Board& board, bool isMax);
private:
    Pyramid_X_O_Board& board;  // Member variable to store the board

};

#endif //SRC_PYRAMIC_TIC_TAC_TOE_H
