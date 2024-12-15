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


class PyramicBoard : public Board<char> {
public:
    PyramicBoard() {
        rows = 3;
        columns = 5;
        board = new char* [rows];
        board[0] = new char[5] { ' ', ' ', ' ', ' ', ' ' };
        board[1] = new char[3] { ' ', ' ', ' ' };
        board[2] = new char[1] { ' ' };
    }

    ~PyramicBoard() {
        for(int i=0; i<rows; i++){
            delete [] board[i];
        }
        delete [] board;
    }

    bool update_board(int x, int y, char symbol) override {
        if (x < 0 || x >= rows || y < 0) return false;
        if (x == 0 && y >= columns) return false;
        if (x == 1 && y >= 3) return false;
        if (x == 2 && y >= 1) return false;

        if(x==0){
            if (board[x][y] == ' ') {
                board[x][y] = symbol;
                n_moves++;
                return true;
            } else {
                return false;
            }
        }else if (x == 1){
            if (board[x][y] == ' ') {
                board[x][y] = symbol;
                n_moves++;
                return true;
            } else {
                return false;
            }
        }else{
            if (board[x][y] == ' ') {
                board[x][y] = symbol;
                n_moves++;
                return true;
            } else {
                return false;
            }
        }

    }

    void display_board() override {
        cout << "        ";
        if(board[2][0] == ' ')
            cout << "__";
        else
            cout << board[2][0] << " ";

        cout << endl;
        cout << "      ";
        for(int i = 0; i < 3; i++){
            if(board[1][i] == ' ')
                cout << "__";
            else
                cout << board[1][i] << " ";
            if(i < 2) cout << "|";
        }
        cout << endl;
        cout << "    ";
        for(int i = 0; i < 5; i++){
            if(board[0][i] == ' ')
                cout << "__";
            else
                cout << board[0][i] << " ";

            if(i < 4) cout << "|";
        }
        cout << endl;
    }


    bool is_win() override {
        //check for wins
        if(board[0][0] != ' ' && board[0][0] == board[0][1] && board[0][1] == board[0][2]) return true;
        if(board[0][1] != ' ' && board[0][1] == board[0][2] && board[0][2] == board[0][3]) return true;
        if(board[0][2] != ' ' && board[0][2] == board[0][3] && board[0][3] == board[0][4]) return true;

        if(board[1][0] != ' ' && board[1][0] == board[1][1] && board[1][1] == board[1][2]) return true;

        if (board[0][0] != ' ' && board[0][0] == board[1][0] && board[1][0] == board[2][0]) return true;
        if (board[0][1] != ' ' && board[0][1] == board[1][1]) return true;
        if (board[0][3] != ' ' && board[0][3] == board[1][2]) return true;
        if (board[0][4] != ' ' && board[0][4] == board[1][2] && board[1][2] == board[2][0]) return true;

        return false;
    }

    bool is_draw() override {
        int empty_count = 0;
        for(int i =0; i < 5; i++){
            if(board[0][i] == ' ')empty_count++;
        }
        for(int i =0; i < 3; i++){
            if(board[1][i] == ' ')empty_count++;
        }
        for(int i =0; i < 1; i++){
            if(board[2][i] == ' ')empty_count++;
        }

        return  (empty_count == 0 && !is_win());
    }
    bool game_is_over() override {
        return is_win() || is_draw();
    }


};

class PyramicRandomPlayer : public RandomPlayer<char> {
public:
    PyramicRandomPlayer(char symbol) : RandomPlayer<char>(symbol) {}
    void getmove(int& x, int& y) override{
        PyramicBoard* b = dynamic_cast<PyramicBoard*>(this->boardPtr);
        do{
            x = rand() % 3;
            if(x ==0){
                y = rand() % 5;
            }else if(x==1){
                y = rand() % 3;
            }else{
                y = rand() % 1;
            }
        }while(b->board[x][y] != ' ');
    }
};

class PyramicHumanPlayer : public Player<char> {
public:
    PyramicHumanPlayer(string n, char symbol) : Player<char>(n, symbol) {}

    void getmove(int& x, int& y) override {
        PyramicBoard* b = dynamic_cast<PyramicBoard*>(this->boardPtr);
        cout << this->getname() << ", enter your move (row, column): ";
        cin >> x >> y;

    }
};

class PyramicDecisionTreePlayer : public Player<char> {
public:
    PyramicDecisionTreePlayer(char symbol) : Player<char>(symbol) {}

    int evaluate_move(PyramicBoard& board, int row, int col, char player_symbol) {
        int score = 0;
        char opponent_symbol = (player_symbol == 'X' ? 'O' : 'X');

        if (row < 0 || row >= board.rows) return -1000;
        if (row == 0 && (col < 0 || col >= board.columns)) return -1000;
        if (row == 1 && (col < 0 || col >= 3)) return -1000;
        if (row == 2 && (col < 0 || col >= 1)) return -1000;
        if (board.board[row][col] != ' ') return -1000;

        // 1. Simulate the Move
        board.board[row][col] = player_symbol;
        // 2. Check if this move causes a win.
        if (board.is_win()) {
            score += 1000; // High score for a winning move
            board.board[row][col] = ' ';
            return score;
        }
        // 3. Check if opponent can win with his next move
        for (int r = 0; r < board.rows; ++r) {
            for (int c = 0; c < board.columns; c++) {
                if(r == 0 && c >= 5) continue;
                if(r == 1 && c >= 3) continue;
                if(r == 2 && c >= 1) continue;
                if(board.board[r][c] == ' '){
                    board.board[r][c] = opponent_symbol;
                    if (board.is_win()) score -= 800; // Very high negative score, almost as important as winning the game.
                    board.board[r][c] = ' ';
                }

            }
        }
        // 4. Check for incomplete lines, give the move a low score if the line is far from being completed.

        if(board.board[0][0] != ' ' && board.board[0][1] != ' ' && board.board[0][2] != ' ') score -= 1;
        if(board.board[0][1] != ' ' && board.board[0][2] != ' ' && board.board[0][3] != ' ') score -= 1;
        if(board.board[0][2] != ' ' && board.board[0][3] != ' ' && board.board[0][4] != ' ') score -= 1;

        if(board.board[1][0] != ' ' && board.board[1][1] != ' ' && board.board[1][2] != ' ') score -= 1;

        if (board.board[0][0] != ' ' && board.board[1][0] != ' ' && board.board[2][0] != ' ') score -= 1;
        if (board.board[0][1] != ' ' && board.board[1][1] != ' ') score -= 1;
        if (board.board[0][3] != ' ' && board.board[1][2] != ' ') score -= 1;
        if (board.board[0][4] != ' ' && board.board[1][2] != ' ' && board.board[2][0] != ' ') score -= 1;


        board.board[row][col] = ' '; // Undo the move
        return score;
    }

    void getmove(int& x, int& y) override {
        PyramicBoard* board = dynamic_cast<PyramicBoard*>(this->boardPtr);
        int best_score = -1000000;
        int best_x = -1, best_y = -1;

        for (int row = 0; row < board->rows; ++row) {
            for (int col = 0; col < board->columns; ++col) {
                if(row == 0 && col >= 5) continue;
                if(row == 1 && col >= 3) continue;
                if(row == 2 && col >= 1) continue;

                int score = evaluate_move(*board, row, col, this->getsymbol());
                if (score > best_score) {
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