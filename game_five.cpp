#include "BoardGame_Classes.h"
#include <iostream>

class NumericalTicTacToe : public Board {
    private:
    vector<int> player1_numbers;
    vector<int> player2_numbers;
    int **num_board;

    bool check_sum_15(int a, int b, int c) {
        return (a + b + c == 15);
    }
public:   
    NumericalTicTacToe();
     bool update_board(int x, int y, char symbol);
    void display_board();
     bool is_winner();
    bool is_draw();
    bool game_is_over();
    ~NumericalTicTacToe();
    };

NumericalTicTacToe::NumericalTicTacToe() {
        n_rows = n_cols = 3;
        n_moves = 0;
        board = new char *[n_rows];
        num_board = new int *[n_rows];
        for (int i = 0; i < n_rows; i++) {
            board[i] = new char[n_cols];
            num_board[i] = new int[n_cols];
            for (int j = 0; j < n_cols; j++) {
                board[i][j] = ' ';
                num_board[i][j] = 0;
            }
        }
    }
     bool NumericalTicTacToe::update_board(int x, int y, char symbol){
         if (x >= 0 && x < n_rows && y >= 0 && y < n_cols && board[x][y] == ' ') {
            int number;
            cout << "Enter the number to place (1-9, odd for Player 1, even for Player 2): ";
            cin >> number;

            if ((symbol == 'X' && (number % 2 == 1) && find(player1_numbers.begin(), player1_numbers.end(), number) == player1_numbers.end()) ||
                (symbol == 'O' && (number % 2 == 0) && find(player2_numbers.begin(), player2_numbers.end(), number) == player2_numbers.end())) {

                board[x][y] = symbol;
                num_board[x][y] = number;
                n_moves++;

                if (symbol == 'X') {
                    player1_numbers.push_back(number);
                } else {
                    player2_numbers.push_back(number);
                }

                return true;
            } else {
                cout << "Invalid number. Try again.\n";
            }
        } else {
            cout << "Invalid move. Try again.\n";
        }

        return false;
     }
    void NumericalTicTacToe::display_board()
     {
        for (int i = 0; i < n_rows; i++) {
            cout << "\n|";
            for (int j = 0; j < n_cols; j++) {
                if (board[i][j] == ' ') {
                    cout << "(" << i << "," << j << ") |";
                } else {
                    cout << " " << num_board[i][j] << "   |";
                }
            }
            cout << "\n---------------------";
        }
        cout << endl;
    }
    
     bool NumericalTicTacToe::is_winner(){
  if (board[0][0] +board[0][1] +board[0][2] == 15)
    {return true;}
    if (board[1][0] + board[1][1] + board[1][2] == 15)
    {return true;}
    if (board[2][0] + board[2][1] + board[2][2] == 15)
    {return true;}
    //check columns
    if (board[0][0] + board[1][0] + board[2][0] == 15)
    {return true;}
    if (board[0][1] + board[1][1] + board[2][1]== 15)
    {return true;}
    if (board[0][2] + board[1][2] + board[2][2] == 15)
    {return true;}
    //check diagonals
    if (board[0][1] + board[1][1] + board[2][2] == 15)
    {return true;}
    if (board[0][2] + board[1][1] + board[2][0] == 15)
    {return true;}
    return false;
     }
    bool NumericalTicTacToe::is_draw(){
          return (n_moves == 9 && !is_winner());
    }
    bool NumericalTicTacToe::game_is_over(){
        return is_winner() || is_draw();
    }
    NumericalTicTacToe::~NumericalTicTacToe() {
        for (int i = 0; i < n_rows; i++) {
            delete[] board[i];
            delete[] num_board[i];
        }
        delete[] board;
        delete[] num_board;
    }