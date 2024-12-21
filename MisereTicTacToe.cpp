// => ** FCAI-CU – CS213 - Object Oriented Programming – 2024 - Assignment ( 2 ) ** <=
// => Last Modification Date: 15/12/2024
// => Under supervision of  : Dr.Mohamed El-Ramly
// => File Name             : CS213_A2_20230417_20230621
// => Purpose               : XO Games using C++
// => Authors               : Malak Mohamed Saad Fahmy Al-Aabiad       => ID: ( 20230417 )    => PROBLEMS:     ( 1, 2, 5, 7, 8 ).
//                          : Mo'men Mohamed Mahmoud Mohamed Yosri     => ID: ( 20230621 )    => PROBLEMS:     ( 3, 4, 6, 9 ).
// => Emails                : malakkalaabiadd@gmail.com
//                          : momen.yosri@gmail.com
// ========================================================================================================================================================================

#include <iostream>
#include <vector>
#include <random>
#include "BoardGame_Classes.h"

using namespace std;
class MisereBoard : public Board<char> {
public:
    MisereBoard() {
        rows = 3;
        columns = 3;
        board = new char* [rows];
        for(int i = 0; i < rows; i++){
            board[i] = new char[columns];
            for(int j = 0; j < columns; j++){
                board[i][j] = ' ';
            }
        }

    }
    ~MisereBoard() {
        for(int i=0; i<rows; i++){
            delete [] board[i];
        }
        delete [] board;
    }

    bool update_board(int x, int y, char symbol) override {
        if (x < 0 || x >= rows || y < 0 || y >= columns) return false;
        if (board[x][y] == ' ') {
            board[x][y] = symbol;
            n_moves++;
            return true;
        }
        return false;
    }

    void display_board() override {
        cout << "\n----------------------";
        for (int i = 0; i < rows; i++) {
            cout << "\n|";
            for (int j = 0; j < columns; j++) {
                if (board[i][j] == ' ') {
                    cout << "(" << i << "," << j << ")" << " |";
                } else {
                    cout << " " << board[i][j] << "   |";
                }
            }
            cout << "\n----------------------";
        }
        cout << endl;
    }

    bool is_win() override {
        for (int i = 0; i < rows; ++i) {
            // Check horizontal
            if (board[i][0] != ' ' && board[i][0] == board[i][1] && board[i][1] == board[i][2]) return true;

            // Check vertical
            if (board[0][i] != ' ' && board[0][i] == board[1][i] && board[1][i] == board[2][i]) return true;
        }

        // Check diagonals
        if (board[0][0] != ' ' && board[0][0] == board[1][1] && board[1][1] == board[2][2]) return true;
        if (board[0][2] != ' ' && board[0][2] == board[1][1] && board[1][1] == board[2][0]) return true;

        return false;
    }

    bool is_draw() override {
        return (n_moves == rows*columns && !is_win());
    }
    bool game_is_over() override {
        return is_win() || is_draw();
    }
};

class MisereRandomPlayer : public RandomPlayer<char> {
public:
    MisereRandomPlayer(char symbol) : RandomPlayer<char>(symbol) {}
    void getmove(int& x, int& y) override{
        MisereBoard* b = dynamic_cast<MisereBoard*>(this->boardPtr);
        do{
            x = rand() % 3;
            y = rand() % 3;
        }while(b->board[x][y] != ' ');
    }
};

class MisereHumanPlayer : public Player<char> {
public:
    MisereHumanPlayer(string n, char symbol) : Player<char>(n, symbol) {}

    void getmove(int& x, int& y) override {
        cout << this->getname() << ", enter your move (row, column): ";
        cin >> x >> y;
    }
};

class MisereDecisionTreePlayer : public Player<char> {
public:
    MisereDecisionTreePlayer(char symbol) : Player<char>(symbol) {}

    int evaluate_move(MisereBoard& board, int row, int col, char player_symbol) {
        int score = 0;
        char opponent_symbol = (player_symbol == 'X' ? 'O' : 'X');

        if (board.board[row][col] != ' ') return -1000; // Invalid move

        board.board[row][col] = player_symbol;

        if (board.is_win()) {
            score = 1000; // This move causes us to lose which is good
            board.board[row][col] = ' '; // Undo
            return score;
        }


        for (int i = 0; i < board.rows; ++i) {
            for (int j = 0; j < board.columns; j++) {
                if (board.board[i][j] == ' ') {
                    board.board[i][j] = opponent_symbol;
                    if (board.is_win())
                        score -=500; // Opponent has a move that will win.
                    board.board[i][j] = ' ';
                }
            }
        }


        // Score based on number of pieces in a row

        int count = 0;
        for(int i = 0; i < board.rows; i++)
        {
            if(board.board[i][0] == player_symbol)
                count++;
            if(board.board[i][1] == player_symbol)
                count++;
            if(board.board[i][2] == player_symbol)
                count++;
            if(count >= 2) score -= (count * count);
            count = 0;
            if(board.board[0][i] == player_symbol)
                count++;
            if(board.board[1][i] == player_symbol)
                count++;
            if(board.board[2][i] == player_symbol)
                count++;
            if (count >= 2) score -= (count * count);
        }
        if(board.board[0][0] == player_symbol && board.board[1][1] == player_symbol) score -= 1;
        if(board.board[0][0] == player_symbol && board.board[2][2] == player_symbol) score -= 1;
        if(board.board[1][1] == player_symbol && board.board[2][2] == player_symbol) score -= 1;
        if(board.board[0][2] == player_symbol && board.board[1][1] == player_symbol) score -= 1;
        if(board.board[0][2] == player_symbol && board.board[2][0] == player_symbol) score -= 1;
        if(board.board[1][1] == player_symbol && board.board[2][0] == player_symbol) score -= 1;

        board.board[row][col] = ' '; // Undo
        return score;
    }


    void getmove(int& x, int& y) override {
        MisereBoard* board = dynamic_cast<MisereBoard*>(this->boardPtr);
        int best_score = -1000000; // Initialize to very low value
        int best_x = -1, best_y = -1;

        for (int row = 0; row < board->rows; ++row) {
            for (int col = 0; col < board->columns; ++col) {
                int score = evaluate_move(*board, row, col, this->getsymbol());
                if (score > best_score) { // Now we look for the highest value
                    best_score = score;
                    best_x = row;
                    best_y = col;
                }
            }
        }

        x = best_x;
        y = best_y;

    }
};