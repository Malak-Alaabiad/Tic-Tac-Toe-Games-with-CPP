#include <iostream>
#include <vector>
#include <random>
#include "BoardGame_Classes.h"
using namespace std;


class FourInARowBoard : public Board<char> {
public:
    FourInARowBoard() {
        rows = 6;
        columns = 7;
        board = new char* [rows];
        for(int i = 0; i < rows; i++){
            board[i] = new char[columns];
            for(int j = 0; j < columns; j++){
                board[i][j] = ' ';
            }
        }
    }
    ~FourInARowBoard() {
        for(int i=0; i<rows; i++){
            delete [] board[i];
        }
        delete [] board;
    }

    bool update_board(int x, int y, char symbol) override {
        if (y < 0 || y >= columns) return false;

        for (int i = rows - 1; i >= 0; --i) {
            if (board[i][y] == ' ') {
                board[i][y] = symbol;
                n_moves++;
                return true;
            }
        }
        return false;
    }

    void display_board() override {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                if(board[i][j] == ' ')
                    cout << "_ ";
                else
                    cout << board[i][j] << " ";
                if(j < columns-1) cout << "|";
            }
            cout << endl;
        }
    }

    bool is_win() override {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                if (board[i][j] != ' ') {
                    char symbol = board[i][j];

                    // Check horizontal
                    if (j + 3 < columns && board[i][j + 1] == symbol && board[i][j + 2] == symbol && board[i][j + 3] == symbol) return true;

                    // Check vertical
                    if (i + 3 < rows && board[i + 1][j] == symbol && board[i + 2][j] == symbol && board[i + 3][j] == symbol) return true;

                    // Check diagonal (top-left to bottom-right)
                    if (i + 3 < rows && j + 3 < columns && board[i + 1][j + 1] == symbol && board[i + 2][j + 2] == symbol && board[i + 3][j + 3] == symbol) return true;

                    // Check diagonal (top-right to bottom-left)
                    if (i + 3 < rows && j - 3 >= 0 && board[i + 1][j - 1] == symbol && board[i + 2][j - 2] == symbol && board[i + 3][j - 3] == symbol) return true;
                }
            }
        }
        return false;
    }

    bool is_draw() override {
        return n_moves == rows * columns && !is_win();
    }

    bool game_is_over() override {
        return is_win() || is_draw();
    }
};

class FourInARowRandomPlayer : public RandomPlayer<char> {
public:
    FourInARowRandomPlayer(char symbol) : RandomPlayer<char>(symbol) {}
    void getmove(int& x, int& y) override{
        FourInARowBoard* b = dynamic_cast<FourInARowBoard*>(this->boardPtr);
        do{
            y = rand() % 7;
            x = 0;
            for(int i = b->rows -1; i >= 0; i--){
                if(b->board[i][y] == ' '){
                    x = i;
                    break;
                }
            }


        }while(x < 0);
    }
};

class FourInARowHumanPlayer : public Player<char> {
public:
    FourInARowHumanPlayer(string n, char symbol) : Player<char>(n, symbol) {}

    void getmove(int& x, int& y) override {
        cout << this->getname() << ", enter your move (column): ";
        cin >> y;
        x = 0;

    }
};