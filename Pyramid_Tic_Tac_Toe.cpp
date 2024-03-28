// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

//
// Created by Dell on 12/17/2023.
//

#include <iostream>
#include <iomanip>
#include"BoardGame_Classes.hpp"
#include"Pyramic_Tic_Tac_Toe.h"


using namespace std;

Pyramid_X_O_Board::Pyramid_X_O_Board(){
    n_rows=3;
    n_cols=5;
    board=new char*[n_rows];
    for(int i{0};i<n_rows;i++){
        board[i]=new char[n_cols];
        for(int j{0};j<n_cols;j++){
            board[i][j]=0;
        }
    }

}

bool Pyramid_X_O_Board:: update_board (int x, int y, char mark)
{
    // Only update if move is valid
    if ((x==0&&y==2||x==1&&y>=1 &&y<4||x==2 &&y>=0&&y<=4 ) && (board[x][y] == 0)) {
        board[x][y] = toupper(mark);
        n_moves++;
        return true;
    } else
        return false;
}




void Pyramid_X_O_Board::display_board() {
    // Display a pyramid-like pattern using specific elements
    int row=3;
    cout << "Pyramid Pattern:\n";
    for (int i = 0; i < 3; i++) {
        cout << setw((3 - i) * 6);  // Adjust spacing based on row number
        for (int j = 2 - i; j < row; j++) {
            cout << "(" << i << "," << j << ")";
            cout << setw(2)<<board[i][j] ;
        }
        row++;

        cout << '\n';
    }

}
bool Pyramid_X_O_Board:: is_winner(){
    // Herizontally (^_^)
    if( (board[1][1]==board[1][2] &&board[1][2]==board[1][3] && board[1][1]!=0 )||
        ( board[2][0]==board[2][1] &&board[2][1]==board[2][2] && board[2][0]!=0)||
        (board[2][1]==board[2][2] &&board[2][2]==board[2][3] &&board[2][1]!=0) ||
        (board[2][2]==board[2][3] &&board[2][3]==board[2][4] &&  board[2][2]!=0)){
        return true;
    }
        //diagonal
    else if( (board[0][2]==board[1][3] &&board[1][3]==board[2][4]&&board[0][2]!=0 )||
             (board[0][2]==board[1][1] && board[1][1]==board[2][0] && board[0][2]!=0) )
        return true;
    else if(board[0][2]==board[1][2] &&board[1][2]==board[2][2] &&board[0][2]!=0)
        return true;
    else
        return false ;

}


// Add this function to your class Pyramid_X_O_Board
int Pyramid_X_O_Board::is_winner_minmax() {
    // Horizontally (^_^)
    if ( board[1][1] == board[1][2] && board[1][2] == board[1][3] && board[1][1] != 0  )
        return (board[1][1] == 'O') ? 2 : -2;  // 0 wins: return 2, X wins: return -2

    if ( board[2][0] == board[2][1] && board[2][1] == board[2][2] && board[2][0] != 0 )
        return (board[2][0] == 'O') ? 2 : -2;  // 0 wins: return 2, X wins: return -2

    if (board[2][1] == board[2][2] && board[2][2] == board[2][3] && board[2][1] != 0)
        return (board[2][1] == 'O') ? 2 : -2;  // 0 wins: return 2, X wins: return -2

    if (board[2][2] == board[2][3] && board[2][3] == board[2][4] && board[2][2] != 0 )
        return (board[2][2] == 'O') ? 2 : -2;  // 0 wins: return 2, X wins: return -2


        // Diagonal + vertical
     if ( (board[0][2] == board[1][3] && board[1][3] == board[2][4] && board[0][2] != 0) ||
     (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != 0)  ||
             (board[0][2]==board[1][2] &&board[1][2]==board[2][2] &&board[0][2]!=0 ) )

         return (board[0][2] == 'O') ? 2 : -2;  // 0 wins: return 2, X wins: return -2


        return 0;  // Tie

    }


bool Pyramid_X_O_Board::is_draw(){
    return (n_moves == 9 && !is_winner());

}
bool Pyramid_X_O_Board::game_is_over(){
    return is_winner()||is_draw();

}
// Pyramid_Random_Player :: Pyramid_Random_Player(char symbol)
//: Player(symbol){
//    name="Random Computer Player";
//    cout<<"My name is " <<name<<endl;
//    cout<<endl;
//}
//void Pyramid_Random_Player :: get_move(int&x , int &y){
//    x=  (int) (rand() % 5);
//    y = (int) (rand() % 3);
//}//---------------------------------------------------------------------------------------------------------


Pyramid_Minimax_Player::Pyramid_Minimax_Player(char symbol,Pyramid_X_O_Board& board) : Player(symbol) , board(board){
    name = "Minimax Computer Player";
    cout << "My name is " << name << endl;
    cout << endl;
}

void Pyramid_Minimax_Player::get_move(int& x, int& y) {
    int bestScore = -1000;
    int moveScore;

    // Loop through all available moves and find the best move
    int row = 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 2 - i; j < row; j++) {
            if (board.is_zero(i, j)) {
                // Make the move
                board.update_board(i, j, symbol);  // <-- Use the symbol of the current player

                // Calculate the score for the current move
                moveScore = minimax(board,  false);

                // Undo the move1
                board.undo(i, j);

                // Update the best move if the current move has a higher score
                if (moveScore > bestScore) {
                    bestScore = moveScore;
                    x = i;
                    y = j;
                }
            }
        }
        row++;
    }
}




int Pyramid_Minimax_Player::minimax(Pyramid_X_O_Board& board,bool isMax) {
    int result = board.is_winner_minmax(); // 2  FOR X , -2 FOR 0 , 0 FOR TIE , 1 FOR NO WINNER

    // Base cases for recursion
    if (result==2 || result==-2 ) { // -2 2 0
        return result;
    }
    // result != 2 and ! =-2
    // result =0
    if( board.is_draw() ) return 0;

    // Recursive case
    if (isMax) {
        int bestScore = -1000;
        int row = 3;
        for (int i = 0; i < 3; i++) {
            for (int j = 2 - i; j < row; j++) {
                if (board.is_zero(i, j)) {
                    // Make the move
                    board.update_board(i, j, symbol);

                    // Recur with the next depth and switch players
                    bestScore = max(bestScore, minimax(board, false));

                    // Undo the move
                    board.undo(i, j);
                }
            }
            row++;
        }
        return bestScore;  // This line was moved outside of the loop

    } else {
        int bestScore = 1000;
        int row = 3;
        for (int i = 0; i < 3; i++) {
            for (int j = 2 - i; j < row; j++) {
                if (board.is_zero(i, j)) {
                    // Make the move
                    board.update_board(i, j, 'X');

                    // Recur with the next depth and switch players
                    bestScore = min(bestScore, minimax(board, true));

                    // Undo the move
                    board.undo(i, j);
                }
            }
            row++;

        }
        return bestScore;
    }

}
