#include "BoardGame_Classes.h"
#include <iostream>

NumericalTicTacToe::NumericalTicTacToe() {
        n_rows = n_cols = 3;
        n_moves = 0;
        board = new char *[n_rows];
        num_board = new int *[n_rows];
        for (int i = 0; i < n_rows; i++) {
            board[i] = new char[n_cols];
            num_board[i] = new int[n_cols];
            for (int j = 0; j < n_cols; j++) {
                board[i][j] = ' ';
                num_board[i][j] = 0;
            }
        }
    }
     bool NumericalTicTacToe::update_board(int x, int y, char symbol){
         if (x >= 0 && x < n_rows && y >= 0 && y < n_cols && board[x][y] == ' ') {
            int number;
            cout << "Enter the number to place (1-9, odd for Player 1, even for Player 2): ";
            cin >> number;

            if ((symbol == 'X' && (number % 2 == 1) && find(player1_numbers.begin(), player1_numbers.end(), number) == player1_numbers.end()) ||
                (symbol == 'O' && (number % 2 == 0) && find(player2_numbers.begin(), player2_numbers.end(), number) == player2_numbers.end())) {

                board[x][y] = symbol;
                num_board[x][y] = number;
                n_moves++;

                if (symbol == 'X') {
                    player1_numbers.push_back(number);
                } else {
                    player2_numbers.push_back(number);
                }

                return true;
            } else {
                cout << "Invalid number. Try again.\n";
            }
        } else {
            cout << "Invalid move. Try again.\n";
        }

        return false;
     }
    void NumericalTicTacToe::display_board(){}
     bool NumericalTicTacToe::is_winner(){}
    bool NumericalTicTacToe::is_draw(){}
    bool NumericalTicTacToe::game_is_over(){}
    NumericalTicTacToe::~NumericalTicTacToe() {
        for (int i = 0; i < n_rows; i++) {
            delete[] board[i];
            delete[] num_board[i];
        }
        delete[] board;
        delete[] num_board;
    }