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
        cout << "\n---------------------------";
        for (int i = 0; i < rows; i++) {
            cout << "\n|";
            for (int j = 0; j < columns; j++) {
                if (board[i][j] == ' ') {
                    cout << "(" << i << "," << j << ")" << " |";
                } else {
                    cout << " " << board[i][j] << "   |";
                }
            }
            cout << "\n---------------------------";
        }
        cout << endl;
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

class FourByFourDecisionTreePlayer : public Player<char> {
public:
    FourByFourDecisionTreePlayer(char symbol) : Player<char>(symbol) {}


    int evaluate_move(FourByFourBoard& board, int row, int col, char player_symbol) {
        int score = 0;
        char opponent_symbol = (player_symbol == 'X' ? 'O' : 'X');

        if (row < 0 || row >= board.rows || col < 0 || col >= board.columns || board.board[row][col] != ' ')
            return -1000; // Invalid move

        board.board[row][col] = player_symbol;

        if (board.is_win()) {
            score += 1000; // High score for a winning move
            board.board[row][col] = ' ';
            return score;
        }

        for (int r = 0; r < board.rows; ++r) {
            for (int c = 0; c < board.columns; ++c) {
                if (board.board[r][c] == ' ') {
                    board.board[r][c] = opponent_symbol;
                    if (board.is_win()) score -= 500;
                    board.board[r][c] = ' ';
                }
            }
        }
        for (int i = 0; i < board.rows; ++i) {
            for (int j = 0; j < board.columns; ++j) {
                if (board.board[i][j] != ' ') {
                    char symbol = board.board[i][j];
                    // Check horizontal
                    int count = 0;
                    if(j + 2 < board.columns)
                    {
                        if(board.board[i][j] == symbol) count++;
                        if(board.board[i][j+1] == symbol) count++;
                        if(board.board[i][j+2] == symbol) count++;
                        if(count >= 2) score -= 1;
                    }
                    count = 0;
                    if(i + 2 < board.rows)
                    {
                        if(board.board[i][j] == symbol) count++;
                        if(board.board[i+1][j] == symbol) count++;
                        if(board.board[i+2][j] == symbol) count++;
                        if(count >= 2) score -= 1;
                    }

                    count = 0;
                    if (i + 2 < board.rows && j + 2 < board.columns)
                    {
                        if(board.board[i][j] == symbol) count++;
                        if(board.board[i+1][j+1] == symbol) count++;
                        if(board.board[i+2][j+2] == symbol) count++;
                        if(count >= 2) score -= 1;
                    }
                    count = 0;
                    if (i + 2 < board.rows && j - 2 >= 0)
                    {
                        if(board.board[i][j] == symbol) count++;
                        if(board.board[i+1][j-1] == symbol) count++;
                        if(board.board[i+2][j-2] == symbol) count++;
                        if(count >= 2) score -= 1;
                    }

                }
            }
        }

        board.board[row][col] = ' '; // Undo the move
        return score;
    }

    void getmove(int& x, int& y) override {
        FourByFourBoard* board = dynamic_cast<FourByFourBoard*>(this->boardPtr);
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