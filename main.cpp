#include "GameManager.cpp"
#include "BoardGame_Classes.h"
#include "game_six.cpp"
int main()
{

    int choice;
    Player *players[2];
    players[0] = new Player(1, 'x');

    cout << "Welcome to FCAI X-O Game. :)\n";
    cout << "please select the game you want to play\n";
    cout << "1- Pyramic Tic-Tac-Toe\n2- Four-in-a-row\n3- 5 x 5 Tic Tac Toe\n4- Normal X_o\n";
    int game;
    cin >> game;
    switch (game)
    {
        case 1:
        {
            cout << "Press 1 if you want to play with computer: ";
            cin >> choice;
            if (choice != 1)
                players[1] = new Player(2, 'o');
            else
                // Player pointer points to child
                players[1] = new RandomPlayer('o', 5);

            GameManager gameMange(new Pyramed_X_O_Board, players);
            gameMange.run();
            break;
        }
        case 2:
        {
            cout << "Press 1 if you want to play with computer: ";
            cin >> choice;
            if (choice != 1)
                players[1] = new Player(2, 'o');
            else
                // Player pointer points to child
                players[1] = new RandomPlayer('o', 7);

            GameManager gameMange(new connect_4_board, players);
            gameMange.run();
            break;
        }
        case 3:
        {
            cout << "Press 1 if you want to play with computer: ";
            cin >> choice;
            if (choice != 1)
                players[1] = new Player(2, 'o');
            else
                // Player pointer points to child
                players[1] = new RandomPlayer('o', 5);

            GameManager gameMange(new X_O_5_Board, players);
            gameMange.run();
            break;
        }
        case 4:
        {
            cout << "Press 1 if you want to play with computer: ";
            cin >> choice;
            if (choice != 1)
                players[1] = new Player(2, 'o');
            else
                // Player pointer points to child
                players[1] = new RandomPlayer('o', 3);

            GameManager gameMange(new X_O_Board, players);
            gameMange.run();
            break;
        }
        case 5:
        {
            NumericalTicTacToe gameBoard;
            cout << "Press 1 if you want to play with computer: ";
            cin >> choice;
            if (choice != 1)
                players[1] = new Player(2, 'o');
            else
                // Player pointer points to child
                players[1] = new RandomPlayer('o', 3);

            GameManager gameManager(&gameBoard, players);
            gameManager.run();
            break;
        }
        case 6:
        {
            players[1] = new Player(1, 'O');
            cout << "Press 1 if you want to play with computer: ";
            cin >> choice;
            if (choice != 1)
                players[0] = new Player(2, 'X');
            else
                // Player pointer points to child
                players[0] = new RandomPlayer('X', 3);

            GameManager gameMange(new MisereTicTacToeBoard() , players);
            gameMange.run();
            break;
        }
        default:
            cout << "run the code agian and input 1 or 2 or 3\n";
    }

    system("pause");
}