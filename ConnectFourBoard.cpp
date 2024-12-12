#include "BoardGame_Classes.h"
// Set the board
connect_4_board::connect_4_board()
{
    n_rows = 6;
    n_cols = 7;
    board = new char *[n_rows];
    for (int i = 0; i < n_rows; i++)
    {
        board[i] = new char[n_cols];
        for (int j = 0; j < n_cols; j++)
        {
            board[i][j] = ' ';
        }
    }
}

// Return true  if move is valid and put it on board
// within board boundaries in empty cell
// Return false otherwise

vector<int> cols_seq = {5, 5, 5, 5, 5, 5, 5};
bool connect_4_board::update_board(int x, int y, char mark)
{
    if ((y >= 0 && y < 7 && cols_seq[y] < 7 && x >= 0 && x < 6 && board[cols_seq[y]][y] == ' '))
    {
        board[cols_seq[y]][y] = toupper(mark);
        n_moves++;
        cols_seq[y]--;
        return true;
    }
    else
    {
        return false;
    }
}

// Display the board and the pieces on it
void connect_4_board::display_board()
{
    for (int i = 0; i < 6; ++i)
    {
        for (int j = 0; j < 7; ++j)
        {
            cout << "| " << board[i][j] << " ";
        }
        cout << "|\n";
    }
    for (int j = 0; j < 7; ++j)
    {
        cout << "----";
    }
    cout << "\n";
    for (int j = 0; j < 7; ++j)
    {
        cout << "  " << j << " ";
    }
    cout << "\n";
}

// Returns true if there is any winner
// either X or O
bool connect_4_board::is_winner()
{
    // row_win[24], col_win[21], diag_left_to_right_win[12], diag_right_to_left_win[12];

    // for the row_win
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (((board[i][j] == board[i][j + 1]) && (board[i][j] == board[i][j + 2]) && (board[i][j] == board[i][j + 3])) && board[i][j] != ' ')
                return true;
        }
    }
    // for the column win
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if ((board[j][i] == board[j + 1][i] && board[j][i] == board[j + 2][i] && board[j][i] == board[j + 3][i]) && board[j][i] != ' ')
                return true;
        }
    }
    // for the left to right diag win
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if ((board[i][j] == board[i + 1][j + 1] && board[i][j] == board[i + 2][j + 2] && board[i][j] == board[i + 3][j + 3]) && board[i][j] != ' ')
                return true;
        }
    }
    // for the right to left diag win
    for (int i = 0; i < 3; i++)
    {
        for (int j = 3; j < 7; j++)
        {
            if ((board[i][j] == board[i + 1][j - 1] && board[i][j] == board[i + 2][j - 2] && board[i][j] == board[i + 3][j - 3]) && board[i][j] != ' ')
                return true;
        }
    }
    return false;
}

bool connect_4_board::is_draw()
{
    return (n_moves == 42 && !is_winner());
}

bool connect_4_board::game_is_over()
{
    return n_moves >= 42;
}