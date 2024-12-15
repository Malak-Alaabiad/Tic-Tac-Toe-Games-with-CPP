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
        for (int i = 0; i < rows; i++) {
            cout << "\n|";
            for (int j = 0; j < columns; j++) {
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
