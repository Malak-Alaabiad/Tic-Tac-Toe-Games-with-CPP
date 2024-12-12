#include "BoardGame_Classes.h"
#include <iostream>

X_O_5_Board::X_O_5_Board()
{
    n_rows = n_cols = 5;
    board = new char *[n_rows];
    for (int i = 0; i < n_rows; i++)
    {
        board[i] = new char[n_cols];
        for (int j = 0; j < n_cols; j++)
            board[i][j] = ' ';
    }
}

// Return true  if move is valid and put it on board
// within board boundaries in empty cell
// Return false otherwise
bool X_O_5_Board::update_board(int x, int y, char mark)
{
    // Only update if move is valid
    if (!(x < 0 || x > 5 || y < 0 || y > 5) && (board[x][y] == ' '))
    {
        board[x][y] = toupper(mark);
        n_moves++;
        return true;
    }
    else
        return false;
}

// Display the board and the pieces on it
void X_O_5_Board::display_board()
{
    for (int i : {0, 1, 2, 3, 4})
    {
        cout << "\n|";
        for (int j : {0, 1, 2, 3, 4})
        {
            if (board[i][j] == ' ')
            {
                cout << "(" << i << "," << j << ")"
                     << " |";
            }
            else
            {
                cout << setw(3) << board[i][j] << "  |";
            }
        }
        cout << "\n-----------------------------";
    }
    cout << endl;
}

bool X_O_5_Board::is_winner()
{
    if (n_moves != 25)
    {
        return false;
    }
    int counterX = 0;
    int counterO = 0;

    // Check rows for winning sequences
    for (int i = 0; i < n_rows; ++i)
    {
        for (int j = 0; j <= n_cols - 3; ++j)
        {
            if (board[i][j] == 'X' && board[i][j + 1] == 'X' && board[i][j + 2] == 'X')
            {
                counterX++; // Increment counter for 'X' for each winning sequence found in a row
            }
            else if (board[i][j] == 'O' && board[i][j + 1] == 'O' && board[i][j + 2] == 'O')
            {
                counterO++; // Increment counter for 'O' for each winning sequence found in a row
            }
        }
    }

    // Check columns for winning sequences
    for (int i = 0; i < n_cols; ++i)
    {
        for (int j = 0; j <= n_rows - 3; ++j)
        {
            if (board[j][i] == 'X' && board[j + 1][i] == 'X' && board[j + 2][i] == 'X')
            {
                counterX++; // Increment counter for 'X' for each winning sequence found in a column
            }
            else if (board[j][i] == 'O' && board[j + 1][i] == 'O' && board[j + 2][i] == 'O')
            {
                counterO++; // Increment counter for 'O' for each winning sequence found in a column
            }
        }
    }

    // Check diagonals for winning sequences
    for (int i = 0; i <= n_rows - 3; ++i)
    {
        for (int j = 0; j <= n_cols - 3; ++j)
        {
            if ((board[i][j] == 'X' && board[i + 1][j + 1] == 'X' && board[i + 2][j + 2] == 'X') ||
                (board[i][j + 2] == 'X' && board[i + 1][j + 1] == 'X' && board[i + 2][j] == 'X'))
            {
                counterX++; // Increment counter for 'X' for each winning sequence found in a diagonal
            }
            else if ((board[i][j] == 'O' && board[i + 1][j + 1] == 'O' && board[i + 2][j + 2] == 'O') ||
                     (board[i][j + 2] == 'O' && board[i + 1][j + 1] == 'O' && board[i + 2][j] == 'O'))
            {
                counterO++; // Increment counter for 'O' for each winning sequence found in a diagonal
            }
        }
    }

    if (counterX > counterO)
    {
        cout << counterX << endl;
        cout << counterO << endl;
        cout << "X is the winner" << endl;
        return true;
    }
    else if (counterO > counterX)
    {
        cout << counterX << endl;
        cout << counterO << endl;
        cout << "O is the winner" << endl;
        return true;
    }
    else
    {
        cout << counterX << endl;
        cout << counterO << endl;
        cout << "It's a draw" << endl;
        return false;
    }
}

// Return true if 25 moves are done and no winner
bool X_O_5_Board::is_draw()
{
    return (n_moves == 25 && !is_winner());
}

bool X_O_5_Board::game_is_over()
{
    return n_moves >= 25;
}

X_O_5_Board::~X_O_5_Board()
{
    delete[] board;
}