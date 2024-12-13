#include "BoardGame_Classes.h"
class MisereTicTacToeBoard : public Board {
public:
    MisereTicTacToeBoard();//
    bool update_board(int x, int y, char mark);
    void display_board();
    bool is_winner();
    bool is_draw();
    bool game_is_over();
    ~MisereTicTacToeBoard();
    };

MisereTicTacToeBoard::MisereTicTacToeBoard() {
    n_rows = n_cols = 3;
        n_moves = 0;
        board = new char *[n_rows];
        for (int i = 0; i < n_rows; i++) {
            board[i] = new char[n_cols];
            for (int j = 0; j < n_cols; j++)
                board[i][j] = ' ';
        }
    }
    bool MisereTicTacToeBoard::update_board(int x, int y, char symbol){
   if (x >= 0 && x < n_rows && y >= 0 && y < n_cols && board[x][y] == ' ') {
            board[x][y] = toupper(symbol);
            n_moves++;
            return true;
        }
        return false;
}
void MisereTicTacToeBoard::display_board(){
    for (int i = 0; i < n_rows; i++) {
            cout << "\n|";
            for (int j = 0; j < n_cols; j++) {
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
bool MisereTicTacToeBoard::is_winner(){
    //check rows
    // Check rows
    if (board[0][0] == board[0][1] && board[0][1] == board[0][2] && board[0][0] != ' ')
    {
        return true;
    }
    if (board[1][0] == board[1][1] && board[1][1] == board[1][2] && board[1][0] != ' ')
    {
        return true;    }
    if (board[2][0] == board[2][1] && board[2][1] == board[2][2] && board[2][0] != ' ')
    {
        return true;    }

// Check columns
    if (board[0][0] == board[1][0] && board[1][0] == board[2][0] && board[0][0] != ' ')
    {
        return true;    }
    if (board[0][1] == board[1][1] && board[1][1] == board[2][1] && board[0][1] != ' ')
    {
        return true;    }
    if (board[0][2] == board[1][2] && board[1][2] == board[2][2] && board[0][2] != ' ')
    {
        return true;    }

    //check columns
   if ((board[0][0] == board[1][1] == board[2][2] ) ||(board[0][2] == board[1][1] == board[2][0]))
   {return true;}
  return false;

}
 bool MisereTicTacToeBoard::is_draw(){
        return (n_moves == 9 && !is_winner());
    }
    bool MisereTicTacToeBoard::game_is_over(){
        return is_winner() || is_draw();
    }
    // bool
    MisereTicTacToeBoard::~MisereTicTacToeBoard(){
     for (int i = 0; i < n_rows; i++) {
            delete[] board[i];
        }
        delete[] board;
}