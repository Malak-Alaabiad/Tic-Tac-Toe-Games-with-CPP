#include <iostream>
#include <vector>
#include <random>
#include "BoardGame_Classes.h"
using namespace std;

class FourByFourBoard : public Board<char> {
public:
    FourByFourBoard() {
        rows = 4;
        columns = 4;
        board = new char* [rows];
        for(int i = 0; i < rows; i++){
            board[i] = new char[columns];
            for(int j = 0; j < columns; j++){
                board[i][j] = ' ';
            }
        }

        board[0][0] = 'X';
        board[0][3] = 'X';
        board[3][0] = 'O';
        board[3][3] = 'O';
    }
    ~FourByFourBoard() {
        for(int i=0; i<rows; i++){
            delete [] board[i];
        }
        delete [] board;
    }
    bool update_board(int x, int y, char symbol) override {

        if(x<0 || x>= rows || y<0 || y>=columns) return false;
        if (board[x][y] != ' ') return false;

        board[x][y] = symbol;
        n_moves++;
        return true;
    }
    void display_board() override {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                cout << board[i][j] << " ";
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
                    if (j + 2 < columns && board[i][j + 1] == symbol && board[i][j + 2] == symbol) return true;

                    // Check vertical
                    if (i + 2 < rows && board[i + 1][j] == symbol && board[i + 2][j] == symbol) return true;

                    // Check diagonal (top-left to bottom-right)
                    if (i + 2 < rows && j + 2 < columns && board[i + 1][j + 1] == symbol && board[i + 2][j + 2] == symbol) return true;

                    // Check diagonal (top-right to bottom-left)
                    if (i + 2 < rows && j - 2 >= 0 && board[i + 1][j - 1] == symbol && board[i + 2][j - 2] == symbol) return true;
                }
            }
        }
        return false;
    }

    bool is_draw() override {
        int empty_count = 0;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                if(board[i][j] == ' ') empty_count++;
            }
        }
        return empty_count == 0 && !is_win();
    }
    bool game_is_over() override {
        return is_win() || is_draw();
    }
};

class FourByFourRandomPlayer : public RandomPlayer<char> {
public:
    FourByFourRandomPlayer(char symbol) : RandomPlayer<char>(symbol) {}
    void getmove(int& x, int& y) override{
        FourByFourBoard* b = dynamic_cast<FourByFourBoard*>(this->boardPtr);
        vector<pair<int, int>> possible_moves;
        for(int i=0; i<b->rows; i++){
            for(int j=0; j<b->columns; j++){
                if (b->board[i][j] == ' ') {
                    // Check up
                    if(i>0 && (b->board[i-1][j] == 'X' || b->board[i-1][j] == 'O' ))
                        possible_moves.push_back({i, j});

                    // Check down
                    if(i < b->rows -1 && (b->board[i+1][j] == 'X' || b->board[i+1][j] == 'O' ))
                        possible_moves.push_back({i, j});
                    // Check left
                    if(j > 0 && (b->board[i][j-1] == 'X' || b->board[i][j-1] == 'O' ))
                        possible_moves.push_back({i, j});
                    // Check right
                    if(j< b->columns -1 && (b->board[i][j+1] == 'X' || b->board[i][j+1] == 'O' ))
                        possible_moves.push_back({i, j});
                }
            }
        }
        if(possible_moves.empty()){
            do{
                x = rand() % 4;
                y = rand() % 4;

            }while(b->board[x][y] != ' ');
        }else{
            int randomIndex = rand() % possible_moves.size();
            x = possible_moves[randomIndex].first;
            y = possible_moves[randomIndex].second;
        }



    }
};

class FourByFourHumanPlayer : public Player<char> {
public:
    FourByFourHumanPlayer(string n, char symbol) : Player<char>(n, symbol) {}

    void getmove(int& x, int& y) override {
        cout << this->getname() << ", enter your move (row, column): ";
        cin >> x >> y;
    }
};