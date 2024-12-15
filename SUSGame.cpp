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

#ifndef GAME9_H
#define GAME9_H

#include "BoardGame_Classes.h"

using namespace std;

int t_p = 0;

template <typename T>
class X_O_Board : public Board<T> {
public:
    int score_p1 = 0, score_p2 = 0;

    X_O_Board() {
        this->rows = this->columns = 3;
        this->board = new char*[this->rows];
        for (int i = 0; i < this->rows; i++) {
            this->board[i] = new char[this->columns];
            for (int j = 0; j < this->columns; j++) {
                this->board[i][j] = '.';
            }
        }
        this->n_moves = 0;
    }

    ~X_O_Board() {
        for (int i = 0; i < this->rows; i++) {
            delete[] this->board[i];
        }
        delete[] this->board;
    }

    bool update_board(int x, int y, T symbol) {
        if (x < 0 || x >= this->rows || y < 0 || y >= this->columns || this->board[x][y] != '.') {
            return false;
        }

        if (symbol == '.') {
            this->n_moves--;
            this->board[x][y] = '.';
        } else {
            this->n_moves++;
            this->board[x][y] = toupper(symbol);
        }

        return true;
    }

    void display_board();
    int check_round();
    void update_score();
    bool is_win();
    bool is_draw();
    bool game_is_over();
};

template <typename T>
class X_O_Player : public Player<T> {
public:
    X_O_Player(string name, T symbol);
    void getmove(int& x, int& y);
};

template <typename T>
class X_O_Random_Player : public RandomPlayer<T> {
public:
    X_O_Random_Player(T symbol);
    void getmove(int& x, int& y);
};

//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <cctype>  // for toupper()

using namespace std;

// Display the board and the pieces on it
template <typename T>
void X_O_Board<T>::display_board() {
    cout << "\n----------------------";
    for (int i = 0; i < this->rows; i++) {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++) {
            if (this->board[i][j] == ' ') {
                cout << "(" << i << "," << j << ")" << " |";
            } else {
                cout << " " << this->board[i][j] << "   |";
            }
        }
        cout << "\n----------------------\n";
    }
    cout << "\nplayer 1 score: "<< this->score_p1<<endl;
    cout <<"player 2 score: "<<this->score_p2<<endl;

    cout << endl;
}

template <typename T>
int X_O_Board<T>::check_round() {
    int count = 0;
    string s1,s2;

    for (int i = 0; i < this->rows; i++) {
        s1={this->board[i][0],this->board[i][1],this->board[i][2]};
        if (s1=="SUS") {
            ++count;
        }
    }
    for (int i = 0; i < this->columns; i++) {
        s2={this->board[0][i],this->board[1][i],this->board[2][i]};
        if (s2=="SUS") {
            ++count;
        }
    }
    s1={this->board[0][0]  ,this->board[1][1] , this->board[2][2]};
    s2={this->board[0][2] , this->board[1][1] ,this->board[2][0]};
    if ( s1== "SUS"){
        ++count;
    }
    if(s2=="SUS"){
        count++;
    }


    return count;
}

template <typename T>
void X_O_Board<T>::update_score() {
    int n = check_round();
    if (this->n_moves % 2 == 1) {  // Player 1's turn (odd moves)
        this->score_p1 += (n - t_p);
        t_p = n;

    } else {  // Player 2's turn (even moves)
        this->score_p2 += (n - t_p);
        t_p = n;

    }
}


template <typename T>
bool X_O_Board<T>::is_win() {
    update_score();
    return this->n_moves == 9 && this->score_p1 != this->score_p2;
}

template <typename T>
bool X_O_Board<T>::is_draw() {
    return this->n_moves == 9 && !is_win();
}

template <typename T>
bool X_O_Board<T>::game_is_over() {
    return is_win() || is_draw();
}
//--------------------------------------

// Constructor for X_O_Player
template <typename T>
X_O_Player<T>::X_O_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void X_O_Player<T>::getmove(int& x, int& y) {

    cout << this->getname()<<"\nPlease enter your move (x y) between 0 and 2: ";
    cin >> x >> y;
}

// Constructor for X_O_Random_Player
template <typename T>
X_O_Random_Player<T>::X_O_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void X_O_Random_Player<T>::getmove(int& x, int& y) {

    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % this->dimension;

}

#endif //GAME9_H