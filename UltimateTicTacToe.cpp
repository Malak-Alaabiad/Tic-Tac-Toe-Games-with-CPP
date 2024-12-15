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
class SubBoard : public Board<char> {
public:
    SubBoard() {
        rows = 3;
        columns = 3;
        board = new char*[3];
        for(int k=0; k < 3; k++){
            board[k] = new char[3]{ ' ', ' ', ' '};
        }
    }

    ~SubBoard() {
        for(int i=0; i < rows; i++){
            delete[] board[i];
        }
        delete[] board;
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
    bool is_win() override {
        for (int i = 0; i < 3; ++i) {
            // Check horizontal
            if (board[i][0] != ' ' && board[i][0] == board[i][1] && board[i][1] == board[i][2]) return true;

            // Check vertical
            if (board[0][i] != ' ' && board[0][i] == board[1][i] && board[1][i] == board[2][i]) return true;
        }
        if (board[0][0] != ' ' && board[0][0] == board[1][1] && board[1][1] == board[2][2]) return true;
        if (board[0][2] != ' ' && board[0][2] == board[1][1] && board[1][1] == board[2][0]) return true;
        return false;
    }

    bool is_draw() override {
        int empty_count = 0;
        for(int i =0; i < rows; i++){
            for(int j =0; j < columns; j++){
                if(board[i][j] == ' ')empty_count++;
            }
        }
        return  (empty_count == 0 && !is_win());
    }

    bool game_is_over() override {
        return is_win() || is_draw();
    }
};
class UltimateBoard : public Board<char> {
public:
    Board<char>*** subBoards;
    char mainBoard[3][3];
    int lastMoveX, lastMoveY;


    bool isSubBoardWin(Board<char>* subBoard, char symbol) {
        char (*b)[3] = (char (*)[3])subBoard->board; // Cast to access the sub-board data directly.

        for (int i = 0; i < 3; ++i) {
            // Check horizontal
            if (b[i][0] == symbol && b[i][0] == b[i][1] && b[i][1] == b[i][2]) return true;

            // Check vertical
            if (b[0][i] == symbol && b[0][i] == b[1][i] && b[1][i] == b[2][i]) return true;
        }
        if (b[0][0] == symbol && b[0][0] == b[1][1] && b[1][1] == b[2][2]) return true;
        if (b[0][2] == symbol && b[0][2] == b[1][1] && b[1][1] == b[2][0]) return true;
        return false;
    }

    bool isSubBoardDraw(Board<char>* subBoard) {
        char (*b)[3] = (char (*)[3])subBoard->board; // Cast to access the sub-board data directly.
        int empty_count =0;
        for(int i=0; i < 3; i++){
            for(int j =0; j < 3; j++){
                if(b[i][j] == ' ') empty_count++;
            }
        }
        return (empty_count == 0 && !isSubBoardWin(subBoard,'X') && !isSubBoardWin(subBoard, 'O'));
    }

public:
    UltimateBoard() {
        rows = 3;
        columns = 3;
        board = new char* [rows];
        for(int i = 0; i < rows; i++){
            board[i] = new char[columns];
            for(int j = 0; j < columns; j++){
                board[i][j] = ' ';
            }
        }

        subBoards = new Board<char>**[3];
        for (int i = 0; i < 3; ++i) {
            subBoards[i] = new Board<char>*[3];
            for (int j = 0; j < 3; ++j) {
                subBoards[i][j] = new SubBoard();

            }
        }
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                mainBoard[i][j] = ' ';
            }
        }

    }
    ~UltimateBoard() {
        for(int i=0; i<rows; i++){
            delete [] board[i];
        }
        delete [] board;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                for(int k=0; k<3; k++){
                    delete [] subBoards[i][j]->board[k];
                }
                delete [] subBoards[i][j]->board;
                delete subBoards[i][j];

            }
            delete[] subBoards[i];
        }
        delete[] subBoards;


    }

    bool update_board(int x, int y, char symbol) override {
        int mainBoardX = x/3;
        int mainBoardY = y/3;
        int subBoardX = x % 3;
        int subBoardY = y % 3;
        if (mainBoard[mainBoardX][mainBoardY] != ' ')
            return false;
        if(subBoards[mainBoardX][mainBoardY]->board[subBoardX][subBoardY] != ' ')
            return false;
        subBoards[mainBoardX][mainBoardY]->board[subBoardX][subBoardY] = symbol;
        lastMoveX = mainBoardX;
        lastMoveY = mainBoardY;

        if(isSubBoardWin(subBoards[mainBoardX][mainBoardY], symbol)){
            mainBoard[mainBoardX][mainBoardY] = symbol;
        } else if (isSubBoardDraw(subBoards[mainBoardX][mainBoardY])) {
            mainBoard[mainBoardX][mainBoardY] = 'D';
        }
        n_moves++;
        return true;
    }

    void display_board() override {
        cout << "Main Board:\n";
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                cout << mainBoard[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;

        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                cout << "Sub-board (" << i << "," << j << "):\n";
                for (int k = 0; k < 3; ++k) {
                    for(int l=0; l < 3; ++l){
                        cout << subBoards[i][j]->board[k][l] << " ";
                    }
                    cout << endl;
                }
                cout << endl;
            }
        }

    }

    bool is_win() override {
        for (int i = 0; i < 3; ++i) {
            if (mainBoard[i][0] != ' ' && mainBoard[i][0] != 'D' && mainBoard[i][0] == mainBoard[i][1] && mainBoard[i][1] == mainBoard[i][2]) return true;
            if (mainBoard[0][i] != ' ' && mainBoard[0][i] != 'D' && mainBoard[0][i] == mainBoard[1][i] && mainBoard[1][i] == mainBoard[2][i]) return true;

        }
        if (mainBoard[0][0] != ' ' && mainBoard[0][0] != 'D' && mainBoard[0][0] == mainBoard[1][1] && mainBoard[1][1] == mainBoard[2][2]) return true;
        if (mainBoard[0][2] != ' ' && mainBoard[0][2] != 'D' && mainBoard[0][2] == mainBoard[1][1] && mainBoard[1][1] == mainBoard[2][0]) return true;
        return false;
    }


    bool is_draw() override {
        int empty_main = 0;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if(mainBoard[i][j] == ' ') empty_main++;
            }
        }

        return (empty_main == 0 && !is_win());
    }
    bool game_is_over() override {
        return is_win() || is_draw();
    }
};

class UltimateRandomPlayer : public RandomPlayer<char> {
public:
    UltimateRandomPlayer(char symbol) : RandomPlayer<char>(symbol) {}
    void getmove(int& x, int& y) override{
        UltimateBoard* b = dynamic_cast<UltimateBoard*>(this->boardPtr);
        int mainBoardX, mainBoardY, subBoardX, subBoardY;

        do{
            mainBoardX = rand() % 3;
            mainBoardY = rand() % 3;
            subBoardX = rand() % 3;
            subBoardY = rand() % 3;
            x = mainBoardX * 3 + subBoardX;
            y = mainBoardY * 3 + subBoardY;

        }while(b->mainBoard[mainBoardX][mainBoardY] != ' ' ||  b->subBoards[mainBoardX][mainBoardY]->board[subBoardX][subBoardY] != ' ');


    }
};

class UltimateHumanPlayer : public Player<char> {
public:
    UltimateHumanPlayer(string n, char symbol) : Player<char>(n, symbol) {}

    void getmove(int& x, int& y) override {
        cout << this->getname() << ", enter your move (row, column - 0 to 8): ";
        cin >> x >> y;
    }
};
