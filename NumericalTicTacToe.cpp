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

class NumericalBoard : public Board<int> {
private:
    vector<int> usedNumbersP1, usedNumbersP2;
public:
    NumericalBoard() {
        rows = 3;
        columns = 3;
        board = reinterpret_cast<char **>(new int *[rows]);
        for(int i = 0; i < rows; i++){
            board[i] = reinterpret_cast<char *>(new int[columns]);
            for(int j = 0; j < columns; j++){
                board[i][j] = 0;
            }
        }
    }

    ~NumericalBoard() {
        for(int i=0; i<rows; i++){
            delete [] board[i];
        }
        delete [] board;
    }
    bool update_board(int x, int y, int symbol) override {
        if (x < 0 || x >= rows || y < 0 || y >= columns) return false;
        if(board[x][y] != 0) return false;
        if (symbol % 2 == 0 && find(usedNumbersP2.begin(), usedNumbersP2.end(), symbol) != usedNumbersP2.end()) return false;
        if (symbol % 2 != 0 && find(usedNumbersP1.begin(), usedNumbersP1.end(), symbol) != usedNumbersP1.end()) return false;

        if(symbol %2 ==0){
            usedNumbersP2.push_back(symbol);
        }else{
            usedNumbersP1.push_back(symbol);
        }
        board[x][y] = symbol;
        n_moves++;
        return true;

    }
    void display_board() override {
        cout << "\n--------------------";
        for (int i = 0; i < this->rows; i++) {
            cout << "\n| ";
            for (int j = 0; j < this->columns; j++) {
                if (this->board[i][j] == ' ') {
                    cout << "(" << i << "," << j << ")" << " |";
                } else {
                    cout << " " << this->board[i][j] << "   |";
                }
            }
            cout << "\n--------------------\n";
        }

        cout << endl;
    }
    bool is_win() override {
        for (int i = 0; i < rows; ++i) {
            // Check horizontal
            if (board[i][0] != 0 && board[i][1] != 0 && board[i][2] != 0) {
                if(board[i][0] + board[i][1] + board[i][2] == 15) return true;
            }
            // Check vertical
            if (board[0][i] != 0 && board[1][i] != 0 && board[2][i] != 0) {
                if(board[0][i] + board[1][i] + board[2][i] == 15) return true;
            }
        }

        if (board[0][0] != 0 && board[1][1] != 0 && board[2][2] != 0) {
            if(board[0][0] + board[1][1] + board[2][2] == 15) return true;
        }
        if (board[0][2] != 0 && board[1][1] != 0 && board[2][0] != 0) {
            if(board[0][2] + board[1][1] + board[2][0] == 15) return true;
        }
        return false;
    }
    bool is_draw() override {
        return (n_moves == rows*columns && !is_win());
    }

    bool game_is_over() override {
        return is_win() || is_draw();
    }
};

class NumericalRandomPlayer : public RandomPlayer<int> {
public:
    NumericalRandomPlayer(int symbol) : RandomPlayer<int>(symbol) {}
    void getmove(int& x, int& y) override{
        NumericalBoard* b = dynamic_cast<NumericalBoard*>(this->boardPtr);
        do{
            x = rand() % 3;
            y = rand() % 3;
        }while(b->board[x][y] != 0);
    }
};
class NumericalHumanPlayer : public Player<int> {
public:
    NumericalHumanPlayer(string n, int symbol) : Player<int>(n, symbol) {}

    void getmove(int& x, int& y) override {
        cout << this->getname() << ", enter your move (row, column): ";
        cin >> x >> y;
        // Add validation for the input
        cout << "Enter your number (1,3,5,7,9 for Player 1 and 2,4,6,8 for Player 2): ";
        int c;
        cin >> c;
        this->symbol = c;

    }
};