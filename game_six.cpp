#include "BoardGame_Classes.h"
#include <iostream>
MisereTicTacToeBoard::MisereTicTacToeBoard() {
        n_rows = n_cols = 3;
        n_moves = 0;
        board = new char *[n_rows];
        for (int i = 0; i < n_rows; i++) {
            board[i] = new char[n_cols];
            for (int j = 0; j < n_cols; j++)
                board[i][j] = ' ';
        }
    }

bool MisereTicTacToeBoard::update_board(int x, int y, char symbol){

   if (x >= 0 && x < n_rows && y >= 0 && y < n_cols && board[x][y] == ' ') {
            board[x][y] = toupper(symbol);
            n_moves++;
            return true;
        }
        return false;
}
void MisereTicTacToeBoard::display_board(){
     for (int i = 0; i < n_rows; i++) {
            cout << "\n|";
            for (int j = 0; j < n_cols; j++) {
                if (board[i][j] == ' ') {
                    cout << "(" << i << "," << j << ")" << " |";
                } else {
                    cout << " " << board[i][j] << "   |";
                }
            }
            cout << "\n---------------------";
        }
        cout << endl;
}
    bool MisereTicTacToeBoard::is_loser(char mark){
        for (int i = 0; i < n_rows; ++i) {
            if (board[i][0] == mark && board[i][1] == mark && board[i][2] == mark)
                return true;
        }

        // Check columns
        for (int i = 0; i < n_cols; ++i) {
            if (board[0][i] == mark && board[1][i] == mark && board[2][i] == mark)
                return true;
        }

        // Check diagonals
        if ((board[0][0] == mark && board[1][1] == mark && board[2][2] == mark) ||
            (board[0][2] == mark && board[1][1] == mark && board[2][0] == mark)) {
            return true;
        }

        return false;}
    bool MisereTicTacToeBoard::is_draw(){
        return (n_moves == 9 && !is_loser('X') && !is_loser('O'));
    }
    bool MisereTicTacToeBoard::game_is_over()
    {return is_loser('X') || is_loser('O') || is_draw();}
MisereTicTacToeBoard::~MisereTicTacToeBoard(){
     for (int i = 0; i < n_rows; i++) {
            delete[] board[i];
        }
        delete[] board;
}