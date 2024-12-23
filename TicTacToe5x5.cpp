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

class FiveByFiveBoard : public Board<char> {
public:
    FiveByFiveBoard() {
        rows = 5;
        columns = 5;
        board = new char* [rows];
        for(int i = 0; i < rows; i++){
            board[i] = new char[columns];
            for(int j = 0; j < columns; j++){
                board[i][j] = ' ';
            }
        }

    }
    ~FiveByFiveBoard() {
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
        cout << "\n------------------------------------";
        for (int i = 0; i < rows; i++) {
            cout << "\n|";
            for (int j = 0; j < columns; j++) {
                if (board[i][j] == ' ') {
                    cout << "(" << i << "," << j << ")" << " |";
                } else {
                    cout << " " << board[i][j] << "   |";
                }
            }
            cout << "\n------------------------------------";
        }
        cout << endl;
    }
    int count_three_in_a_row(char symbol) {
        int count = 0;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                if (board[i][j] == symbol) {
                    // Check horizontal
                    if (j + 2 < columns && board[i][j + 1] == symbol && board[i][j + 2] == symbol) count++;

                    // Check vertical
                    if (i + 2 < rows && board[i + 1][j] == symbol && board[i + 2][j] == symbol) count++;

                    // Check diagonal (top-left to bottom-right)
                    if (i + 2 < rows && j + 2 < columns && board[i + 1][j + 1] == symbol && board[i + 2][j + 2] == symbol) count++;

                    // Check diagonal (top-right to bottom-left)
                    if (i + 2 < rows && j - 2 >= 0 && board[i + 1][j - 1] == symbol && board[i + 2][j - 2] == symbol) count++;

                }
            }
        }
        return count;
    }
    bool is_win() override {
        // This is not a win-lose game, but the 3 in a row should be counted in the is_draw method
        return false;
    }

    bool is_draw() override {
        if(n_moves < 24)
            return false;
        int p1 = count_three_in_a_row('X');
        int p2 = count_three_in_a_row('O');

        cout << "Player 1 (X) has " << p1 << " sequences of 3 in a row\n";
        cout << "Player 2 (O) has " << p2 << " sequences of 3 in a row\n";
        if(p1 > p2){
            cout << "Player 1 Wins!\n";
            return true;
        }else if(p2 > p1){
            cout << "Player 2 Wins!\n";
            return true;
        }else{
            cout << "Draw\n";
            return true;
        }

    }
    bool game_is_over() override {
        return  is_draw();
    }
};

class FiveByFiveRandomPlayer : public RandomPlayer<char> {
public:
    FiveByFiveRandomPlayer(char symbol) : RandomPlayer<char>(symbol) {}
    void getmove(int& x, int& y) override{
        FiveByFiveBoard* b = dynamic_cast<FiveByFiveBoard*>(this->boardPtr);
        do{
            x = rand() % 5;
            y = rand() % 5;
        }while(b->board[x][y] != ' ');
    }
};

class FiveByFiveHumanPlayer : public Player<char> {
public:
    FiveByFiveHumanPlayer(string n, char symbol) : Player<char>(n, symbol) {}

    void getmove(int& x, int& y) override {
        cout << this->getname() << ", enter your move (row, column): ";
        cin >> x >> y;
    }
};

class FiveByFiveDecisionTreePlayer : public Player<char> {
public:
    FiveByFiveDecisionTreePlayer(char symbol) : Player<char>(symbol) {}

    int evaluate_move(FiveByFiveBoard& board, int row, int col, char player_symbol) {
        int score = 0;
        char opponent_symbol = (player_symbol == 'X' ? 'O' : 'X');

        if (row < 0 || row >= board.rows || col < 0 || col >= board.columns || board.board[row][col] != ' ')
            return -1000; // Invalid move

        board.board[row][col] = player_symbol;

        // Check for the number of three in a rows after this move
        score = board.count_three_in_a_row(player_symbol);

        // Check what the other player would do after this
        for (int r = 0; r < board.rows; ++r) {
            for (int c = 0; c < board.columns; ++c) {
                if (board.board[r][c] == ' ') {
                    board.board[r][c] = opponent_symbol;
                    score -= board.count_three_in_a_row(opponent_symbol);
                    board.board[r][c] = ' ';
                }
            }
        }
        board.board[row][col] = ' ';
        return score;

    }
    void getmove(int& x, int& y) override {
        FiveByFiveBoard* board = dynamic_cast<FiveByFiveBoard*>(this->boardPtr);
        int best_score = -1000000;
        int best_x = -1, best_y = -1;

        for (int row = 0; row < board->rows; ++row) {
            for (int col = 0; col < board->columns; ++col) {
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