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