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
#include <memory>
#include <random>
#include "BoardGame_Classes.h"
#include "PyramicTicTacToe.cpp"
#include "FourInRow.cpp"
#include "TicTacToe5x5.cpp"
#include "WordTicTacToe.cpp"
#include "NumericalTicTacToe.cpp"
#include "MisereTicTacToe.cpp"
#include "TicTacToe4x4.cpp"
#include "UltimateTicTacToe.cpp"
#include "SUSGame.cpp"

using namespace std;

int main() {
    srand(time(0)); // Seed the random number generator

    while (true) {
        cout << "\nChoose a game:\n";
        cout << "1. Pyramic Tic-Tac-Toe\n";
        cout << "2. Four-in-a-Row\n";
        cout << "3. 5x5 Tic-Tac-Toe\n";
        cout << "4. Word Tic-Tac-Toe\n";
        cout << "5. Numerical Tic-Tac-Toe\n";
        cout << "6. Misere Tic-Tac-Toe\n";
        cout << "7. 4x4 Tic-Tac-Toe\n";
        cout << "8. Ultimate Tic-Tac-Toe\n";
        cout << "9. SUS Game\n";
        cout << "0. Exit\n";

        int choice;
        cout << "Enter your choice: ";
        cin >> choice;
        if (choice == 0) {
            cout << "Exiting...\n";
            break;
        }


        Board<char>* boardPtr = nullptr;
        Player<char>* playerPtr[2] = {nullptr, nullptr};

        switch (choice) {
            case 1: {
                boardPtr = new PyramicBoard();
                cout << "\nPlay against AI (1) or Human (2)?: ";
                int type;
                cin >> type;
                if (type == 1) {
                    playerPtr[0] = new PyramicHumanPlayer("Player 1", 'X');
                    playerPtr[1] = new PyramicRandomPlayer('O');
                } else {
                    playerPtr[0] = new PyramicHumanPlayer("Player 1", 'X');
                    playerPtr[1] = new PyramicHumanPlayer("Player 2", 'O');
                }
                break;
            }
            case 2: {
                boardPtr = new FourInARowBoard();
                cout << "\nPlay against:\n";
                cout << "1. Random Computer AI\n";
                cout << "2. Decision Tree AI\n";
                cout << "3. Human Player\n";
                cout << "Enter your choice: ";
                int type;
                cin >> type;

                playerPtr[0] = new FourInARowHumanPlayer("Player 1", 'X');

                switch (type) {
                    case 1:
                        playerPtr[1] = new FourInARowRandomPlayer('O');
                        break;
                    case 2:
                        playerPtr[1] = new FourInARowDecisionTreePlayer('O');
                        break;
                    case 3:
                        playerPtr[1] = new FourInARowHumanPlayer("Player 2", 'O');
                        break;
                    default:
                        cout << "Invalid choice. Defaulting to Human vs Human.\n";
                        playerPtr[1] = new FourInARowHumanPlayer("Player 2", 'O');
                        break;
                }
                break;
            }
            case 3: {
                boardPtr = new FiveByFiveBoard();
                cout << "\nPlay against AI (1) or Human (2)?: ";
                int type;
                cin >> type;
                if (type == 1) {
                    playerPtr[0] = new FiveByFiveHumanPlayer("Player 1", 'X');
                    playerPtr[1] = new FiveByFiveRandomPlayer('O');
                } else {
                    playerPtr[0] = new FiveByFiveHumanPlayer("Player 1", 'X');
                    playerPtr[1] = new FiveByFiveHumanPlayer("Player 2", 'O');
                }
                break;
            }
            case 4: {
                try {
                    boardPtr = new WordBoard();
                    cout << "\nPlay against AI (1) or Human (2)?: ";
                    int type;
                    cin >> type;
                    if (type == 1) {
                        playerPtr[0] = new WordHumanPlayer("Player 1", ' ');
                        playerPtr[1] = new WordRandomPlayer(' ');
                    } else {
                        playerPtr[0] = new WordHumanPlayer("Player 1", ' ');
                        playerPtr[1] = new WordHumanPlayer("Player 2", ' ');
                    }
                } catch (const std::runtime_error &e) {
                    cerr << e.what() << endl;
                    continue;
                }
                break;
            }
            case 5: {
                // Display welcome message and the explanation of the problem to the user
                cout << "\n--------------------------------------------------------------";
                cout << endl << "||          ** Welcome To Numerical Tic-Tac-Toe  **        ||";
                cout << "\n--------------------------------------------------------------";
                boardPtr = reinterpret_cast<Board<char> *>(new NumericalBoard());
                cout << "\nPlay against AI (1) or Human (2)?: ";
                int type;
                cin >> type;
                if (type == 1) {
                    playerPtr[0] = reinterpret_cast<Player<char> *>(new NumericalHumanPlayer("Player 1", 1));
                    playerPtr[1] = reinterpret_cast<Player<char> *>(new NumericalRandomPlayer(2));
                } else {
                    playerPtr[0] = reinterpret_cast<Player<char> *>(new NumericalHumanPlayer("Player 1", 1));
                    playerPtr[1] = reinterpret_cast<Player<char> *>(new NumericalHumanPlayer("Player 2", 2));
                    break;
                }
                case 6: {
                    boardPtr = new MisereBoard();
                    cout << "\nPlay against AI (1) or Human (2)?: ";
                    int type;
                    cin >> type;
                    if (type == 1) {
                        playerPtr[0] = new MisereHumanPlayer("Player 1", 'X');
                        playerPtr[1] = new MisereRandomPlayer('O');
                    } else {
                        playerPtr[0] = new MisereHumanPlayer("Player 1", 'X');
                        playerPtr[1] = new MisereHumanPlayer("Player 2", 'O');
                    }
                    break;
                }
                case 7: {
                    boardPtr = new FourByFourBoard();
                    cout << "\nPlay against AI (1) or Human (2)?: ";
                    int type;
                    cin >> type;
                    if (type == 1) {
                        playerPtr[0] = new FourByFourHumanPlayer("Player 1", 'X');
                        playerPtr[1] = new FourByFourRandomPlayer('O');
                    } else {
                        playerPtr[0] = new FourByFourHumanPlayer("Player 1", 'X');
                        playerPtr[1] = new FourByFourHumanPlayer("Player 2", 'O');
                    }
                    break;
                }
                case 8: {
                    boardPtr = new UltimateBoard();
                    cout << "\nPlay against AI (1) or Human (2)?: ";
                    int type;
                    cin >> type;
                    if (type == 1) {
                        playerPtr[0] = new UltimateHumanPlayer("Player 1", 'X');
                        playerPtr[1] = new UltimateRandomPlayer('O');
                    } else {
                        playerPtr[0] = new UltimateHumanPlayer("Player 1", 'X');
                        playerPtr[1] = new UltimateHumanPlayer("Player 2", 'O');
                    }
                    break;
                }
                case 9: {
                    // Display welcome message and the explanation of the problem to the user
                    cout << "\n--------------------------------------------------------------";
                    cout << endl << "||          ** Welcome To SUS Game  **                     ||";
                    cout << "\n--------------------------------------------------------------";
                    int choice;
                    Player<char> *players[2];
                    X_O_Board<char> *B = new X_O_Board<char>();
                    string playerXName, player2Name;
                    // Set up player 1
                    cout << "\nEnter Player X name: ";
                    cin >> playerXName;
                    cout << "Choose Player X type:\n";
                    cout << "1. Human\n";
                    cout << "2. Random Computer\n";
                    cin >> choice;

                    switch (choice) {
                        case 1:
                            players[0] = new X_O_Player<char>(playerXName, 'S');
                            break;
                        case 2:
                            players[0] = new X_O_Random_Player<char>('S');
                            break;
                        default:
                            cout << "Invalid choice for Player 1. Exiting the game.\n";
                    }

                    // Set up player 2
                    cout << "Enter Player 2 name: ";
                    cin >> player2Name;
                    cout << "Choose Player 2 type:\n";
                    cout << "1. Human\n";
                    cout << "2. Random Computer\n";
                    cin >> choice;

                    switch (choice) {
                        case 1:
                            players[1] = new X_O_Player<char>(player2Name, 'U');
                            break;
                        case 2:
                            players[1] = new X_O_Random_Player<char>('U');
                            break;
                        default:
                            cout << "Invalid choice for Player 2. Exiting the game.\n";
                    }

                    // Create the game manager and run the game
                    GameManager<char> x_o_game(B, players);
                    x_o_game.run();

                    // Clean up
                    delete B;
                    for (int i = 0; i < 2; ++i) {
                        delete players[i];
                    }
                }

                default:
                    cout << "Invalid choice. Please try again.\n";
                continue;
            }
        }

        if (boardPtr != nullptr && playerPtr[0] != nullptr && playerPtr[1] != nullptr) {
            playerPtr[0]->setBoard(boardPtr);
            playerPtr[1]->setBoard(boardPtr);
            GameManager<char> gameManager(boardPtr, playerPtr);
            gameManager.run();


        }
        delete boardPtr;
        delete playerPtr[0];
        delete playerPtr[1];

        boardPtr = nullptr;
        playerPtr[0] = nullptr;
        playerPtr[1] = nullptr;

    }
    return 0;
}