#include "BoardGame_Classes.h"

Pyramed_X_O_Board::Pyramed_X_O_Board()
{
    n_moves = 0;
    n_cols = 5;
    n_rows = 3;
    board = new char *[n_rows];
    for (size_t i = 0; i < n_rows; i++)
    {
        board[i] = new char[i * 2 + 1];
        for (size_t j = 0; j < i * 2 + 1; j++)
        {
            board[i][j] = ' ';
        }
    }
}
bool Pyramed_X_O_Board::update_board(int x, int y, char mark)
{
    if (n_moves == 9)
    {
        return false;
    }
    if (x < n_rows && x > -1 && y < n_cols && y > -1)
    {
        if (board[x][y] != ' ')
        {

            return false;
        }
        board[x][y] = mark;
        n_moves++;
        return true;
    }
    else
        return false;
}

void Pyramed_X_O_Board::display_board()
{
    cout << "======================\n";
    for (size_t i = 0; i < n_rows; i++)
    {
        if (i == 0)
        {
            cout << "   |";
        }
        if (i == 1)
        {
            cout << " |";
        }
        for (size_t j = 0; j < i * 2 + 1; j++)
        {
            if (board[i][j] != ' ')
                cout << board[i][j] << "|";
            else
                cout << "(" << i << ',' << j << ")|";
        }
        cout << "\n-----------------------\n";
    }
    cout << "======================\n";
}

bool Pyramed_X_O_Board::is_winner()
{

    if (board[2][2] == board[1][1] && board[0][0] == board[2][2] && board[2][2] != ' ')
    {
        return true;
    }
    else if (board[1][2] == board[1][0] && board[1][1] == board[1][0] && board[1][1] != ' ')
    {
        return true;
    }
    else if (board[0][0] == board[1][2] && board[1][2] == board[2][4] && board[0][0] != ' ')
    {
        return true;
    }
    else if (board[0][0] == board[2][0] && board[1][0] == board[0][0] && board[0][0] != ' ')
    {
        return true;
    }
    else
    {
        for (size_t i = 0; i < 3; i++)
        {
            if (board[2][0 + i] == board[2][1 + i] && board[2][2 + i] == board[2][1 + i] && board[2][0 + i] != ' ')
            {
                return true;
            }
        }
    }

    return false;
}
bool Pyramed_X_O_Board::is_draw()
{
    if (n_moves == 9)
    {
        return true;
    }
    else
        return false;
}
bool Pyramed_X_O_Board ::game_is_over()
{
    if (n_moves == 9)
    {
        return true;
    }
    return false;
}

Pyramed_X_O_Board::~Pyramed_X_O_Board()
{
    delete[] board;
}