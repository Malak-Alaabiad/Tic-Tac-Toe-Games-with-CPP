// => ** FCAI-CU – CS213 - Object Oriented Programming – 2024 - Assignment ( 2 ) ** <=
// => Last Modification Date: 15/12/2024
// => Under supervision of  : Dr.Mohamed El-Ramly
// => File Name             : CS213_A2_20230417_20230621
// => Purpose               : XO Games using C++
// => Authors               : Malak Mohamed Saad Fahmy Al-Aabiad       => ID: ( 20230417 )    => PROBLEMS:     ( 1, 2, 5, 7, 8 ).
//                          : Mo'men Mohamed Mahmoud Mohamed Yosri     => ID: ( 20230621 )    => PROBLEMS:     ( 3, 4, 6, 9 ).
// => Emails                : malakkalaabiadd@gmail.com
//                          : momen.yosri@gmail.com
// ===============================================================================================================================

#include "bits/stdc++.h"
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
        cout << "\n--------------------------------------------------";
        for (int i = 0; i < rows; i++) {
            cout << "\n|";
            for (int j = 0; j < columns; j++) {
                if (board[i][j] == ' ') {
                    cout << "(" << i << "," << j << ")" << " |";
                } else {
                    cout << " " << board[i][j] << "   |";
                }
            }
            cout << "\n--------------------------------------------------\n";
        }
        cout << endl;
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

//--------------------- Decision Tree Player ----------------------------------
class FourInARowDecisionTreePlayer : public Player<char> {
public:
    FourInARowDecisionTreePlayer(char symbol) : Player<char>(symbol) {}

    int evaluate_move(FourInARowBoard& board, int column, char player_symbol) {
        int score = 0;
        char opponent_symbol = (player_symbol == 'X' ? 'O' : 'X');

        int row = -1;
        for (int i = board.rows - 1; i >= 0; --i) {
            if (board.board[i][column] == ' ') {
                row = i;
                break;
            }
        }

        if (row == -1) return -1000;  // Invalid move

        // Simulate the move
        board.board[row][column] = player_symbol;


        // Check for winning move
        if(board.is_win()){
            score += 1000;
        } else {
            // Check for potential wins for the opponent
            for(int c = 0; c < board.columns; c++) {
                int r = -1;
                for (int i = board.rows - 1; i >= 0; --i) {
                    if (board.board[i][c] == ' ') {
                        r = i;
                        break;
                    }
                }

                if (r != -1) {
                    board.board[r][c] = opponent_symbol;
                    if(board.is_win()) score -= 500;
                    board.board[r][c] = ' '; //Undo
                }
            }
        }


        // Score based on number of pieces in a row
        for(int i = 0; i < board.rows; i++)
        {
            for (int j = 0; j < board.columns; j++)
            {
                if(board.board[i][j] == player_symbol)
                {
                    // horizontal
                    int count = 0;
                    for (int k = j; k < board.columns; k++)
                        if (board.board[i][k] == player_symbol)
                            count++;
                        else
                            break;

                    if (count >= 2)
                        score += (count * count); // Adjust the scoring system based on number of pieces

                    // vertical
                    count = 0;
                    for (int k = i; k < board.rows; k++)
                        if (board.board[k][j] == player_symbol)
                            count++;
                        else
                            break;

                    if (count >= 2)
                        score += (count * count);

                    // Diagonal right
                    count = 0;
                    for (int k = 0; k < board.rows; k++)
                        if (i + k < board.rows && j + k < board.columns && board.board[i + k][j + k] == player_symbol)
                            count++;
                        else
                            break;
                    if (count >= 2)
                        score += (count * count);

                    // diagonal left
                    count = 0;
                    for(int k = 0; k < board.rows; k++)
                        if (i + k < board.rows && j - k >=0 && board.board[i + k][j - k] == player_symbol)
                            count++;
                        else
                            break;
                    if(count >= 2)
                        score += (count * count);

                }
            }
        }

        board.board[row][column] = ' '; // Undo the move
        return score;
    }

    void getmove(int& x, int& y) override {
        FourInARowBoard* board = dynamic_cast<FourInARowBoard*>(this->boardPtr);
        int best_score = -100000;
        int best_move = -1;
        for (int column = 0; column < board->columns; column++) {
            int score = evaluate_move(*board, column, this->getsymbol());
            if (score > best_score) {
                best_score = score;
                best_move = column;
            }
        }
        y = best_move;
        x = 0;

        for (int i = board->rows - 1; i >= 0; i--) {
            if (board->board[i][y] == ' ') {
                x = i;
                break;
            }
        }
    }
};