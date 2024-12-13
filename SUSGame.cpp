#include <iostream>
#include <vector>
#include <random>
#include "BoardGame_Classes.h"
using namespace std;

class SUSBoard : public Board<char> {
public:
    SUSBoard() {
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
    ~SUSBoard() {
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
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                cout << board[i][j] << " ";
            }
            cout << endl;
        }
    }

    int count_sus() {
        int count = 0;
        for (int i = 0; i < rows; ++i) {
            // Check horizontal
            if (board[i][0] == 'S' && board[i][1] == 'U' && board[i][2] == 'S') count++;

            // Check vertical
            if (board[0][i] == 'S' && board[1][i] == 'U' && board[2][i] == 'S') count++;

        }

        if (board[0][0] == 'S' && board[1][1] == 'U' && board[2][2] == 'S') count++;
        if (board[0][2] == 'S' && board[1][1] == 'U' && board[2][0] == 'S') count++;
        return count;

    }
    bool is_win() override {
        //This is not a win-lose game, but the number of SUS will determine the winner in the is_draw method
        return false;
    }

    bool is_draw() override {
        if(n_moves < rows*columns) return false;
        int p1 = count_sus();
        cout << "Number of SUS sequences: " << p1 << "\n";
        return true;
    }
    bool game_is_over() override {
        return is_draw();
    }
};

class SUSRandomPlayer : public RandomPlayer<char> {
public:
    SUSRandomPlayer(char symbol) : RandomPlayer<char>(symbol) {}
    void getmove(int& x, int& y) override{
        SUSBoard* b = dynamic_cast<SUSBoard*>(this->boardPtr);
        do{
            x = rand() % 3;
            y = rand() % 3;
        }while(b->board[x][y] != ' ');

    }
};

class SUSHumanPlayer : public Player<char> {
public:
    SUSHumanPlayer(string n, char symbol) : Player<char>(n, symbol) {}

    void getmove(int& x, int& y) override {
        cout << this->getname() << ", enter your move (row, column): ";
        cin >> x >> y;
        // Add validation for the input
        cout << "Enter your letter (S or U): ";
        char c;
        cin >> c;
        this->symbol = c;
    }
};