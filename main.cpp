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
    srand(time(0));

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

        unique_ptr<Board<char>> boardPtr;
        unique_ptr<Player<char>> playerPtr[2];

        switch (choice) {
            case 1: {
                boardPtr.reset(new PyramicBoard());
                cout << "\nPlay against:\n";
                cout << "1. Random Computer AI\n";
                cout << "2. Decision Tree AI\n";
                cout << "3. Human Player\n";
                cout << "Enter your choice: ";
                int type;
                cin >> type;

                playerPtr[0].reset(new PyramicHumanPlayer("Player 1", 'X'));


                switch (type) {
                    case 1:
                        playerPtr[1].reset(new PyramicRandomPlayer('O'));
                        break;
                    case 2:
                        playerPtr[1].reset(new PyramicDecisionTreePlayer('O'));
                        break;
                    case 3:
                        playerPtr[1].reset(new PyramicHumanPlayer("Player 2", 'O'));
                        break;
                    default:
                        cout << "Invalid choice. Defaulting to Human vs Human.\n";
                        playerPtr[1].reset(new PyramicHumanPlayer("Player 2", 'O'));
                        break;
                }
                break;
            }
            case 2: {
                boardPtr.reset(new FourInARowBoard());
                cout << "\nPlay against:\n";
                cout << "1. Random Computer AI\n";
                cout << "2. Decision Tree AI\n";
                cout << "3. Human Player\n";
                cout << "Enter your choice: ";
                int type;
                cin >> type;

                playerPtr[0].reset(new FourInARowHumanPlayer("Player 1", 'X'));

                switch (type) {
                    case 1:
                        playerPtr[1].reset(new FourInARowRandomPlayer('O'));
                        break;
                    case 2:
                        playerPtr[1].reset(new FourInARowDecisionTreePlayer('O'));
                        break;
                    case 3:
                        playerPtr[1].reset(new FourInARowHumanPlayer("Player 2", 'O'));
                        break;
                    default:
                        cout << "Invalid choice. Defaulting to Human vs Human.\n";
                        playerPtr[1].reset(new FourInARowHumanPlayer("Player 2", 'O'));
                        break;
                }
                break;
            }
            case 3: {
                boardPtr.reset(new FiveByFiveBoard());
                cout << "\nPlay against:\n";
                cout << "1. Random Computer AI\n";
                cout << "2. Decision Tree AI\n";
                cout << "3. Human Player\n";
                cout << "Enter your choice: ";
                int type;
                cin >> type;

                playerPtr[0].reset(new FiveByFiveHumanPlayer("Player 1", 'X'));


                switch (type) {
                    case 1:
                        playerPtr[1].reset(new FiveByFiveRandomPlayer('O'));
                        break;
                    case 2:
                        playerPtr[1].reset(new FiveByFiveDecisionTreePlayer('O'));
                        break;
                    case 3:
                        playerPtr[1].reset(new FiveByFiveHumanPlayer("Player 2", 'O'));
                        break;
                    default:
                        cout << "Invalid choice. Defaulting to Human vs Human.\n";
                        playerPtr[1].reset(new FiveByFiveHumanPlayer("Player 2", 'O'));
                        break;
                }
                break;
            }
            case 4: {
                try {
                    boardPtr.reset(new WordBoard());
                    cout << "\nPlay against AI (1) or Human (2)?: ";
                    int type;
                    cin >> type;
                    if (type == 1) {
                        playerPtr[0].reset(new WordHumanPlayer("Player 1", ' '));
                        playerPtr[1].reset(new WordRandomPlayer(' '));
                    } else {
                        playerPtr[0].reset(new WordHumanPlayer("Player 1", ' '));
                        playerPtr[1].reset(new WordHumanPlayer("Player 2", ' '));
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
                boardPtr.reset(reinterpret_cast<Board<char> *>(new NumericalBoard()));
                cout << "\nPlay against:\n";
                cout << "1. Random Computer AI\n";
                cout << "2. Decision Tree AI\n";
                cout << "3. Human Player\n";
                cout << "Enter your choice: ";
                int type;
                cin >> type;

                playerPtr[0].reset(reinterpret_cast<Player<char> *>(new NumericalHumanPlayer("Player 1", 1)));

                switch (type) {
                    case 1:
                        playerPtr[1].reset(reinterpret_cast<Player<char> *>(new NumericalRandomPlayer(2)));
                        break;
                    case 2:
                        playerPtr[1].reset(reinterpret_cast<Player<char> *>(new NumericalDecisionTreePlayer(2)));
                        break;
                    case 3:
                        playerPtr[1].reset(reinterpret_cast<Player<char> *>(new NumericalHumanPlayer("Player 2", 2)));
                        break;
                    default:
                        cout << "Invalid choice. Defaulting to Human vs Human.\n";
                        playerPtr[1].reset(reinterpret_cast<Player<char> *>(new NumericalHumanPlayer("Player 2", 2)));
                        break;
                }
                break;

                case 6: {
                    boardPtr.reset(new MisereBoard());
                    cout << "\nPlay against:\n";
                    cout << "1. Random Computer AI\n";
                    cout << "2. Decision Tree AI\n";
                    cout << "3. Human Player\n";
                    cout << "Enter your choice: ";
                    int type;
                    cin >> type;

                    playerPtr[0].reset(new MisereHumanPlayer("Player 1", 'X'));

                    switch (type) {
                        case 1:
                            playerPtr[1].reset(new MisereRandomPlayer('O'));
                            break;
                        case 2:
                            playerPtr[1].reset(new MisereDecisionTreePlayer('O'));
                            break;
                        case 3:
                            playerPtr[1].reset(new MisereHumanPlayer("Player 2", 'O'));
                            break;
                        default:
                            cout << "Invalid choice. Defaulting to Human vs Human.\n";
                            playerPtr[1].reset(new MisereHumanPlayer("Player 2", 'O'));
                            break;
                    }
                    break;
                }
                case 7: {
                    boardPtr.reset(new FourByFourBoard());
                    cout << "\nPlay against:\n";
                    cout << "1. Random Computer AI\n";
                    cout << "2. Decision Tree AI\n";
                    cout << "3. Human Player\n";
                    cout << "Enter your choice: ";
                    int type;
                    cin >> type;

                    playerPtr[0].reset(new FourByFourHumanPlayer("Player 1", 'X'));

                    switch (type) {
                        case 1:
                            playerPtr[1].reset(new FourByFourRandomPlayer('O'));
                            break;
                        case 2:
                            playerPtr[1].reset(new FourByFourDecisionTreePlayer('O'));
                            break;
                        case 3:
                            playerPtr[1].reset(new FourByFourHumanPlayer("Player 2", 'O'));
                            break;
                        default:
                            cout << "Invalid choice. Defaulting to Human vs Human.\n";
                            playerPtr[1].reset(new FourByFourHumanPlayer("Player 2", 'O'));
                            break;
                    }
                    break;
                }
                case 8: {
                    boardPtr.reset(new UltimateBoard());
                    cout << "\nPlay against:\n";
                    cout << "1. Random Computer AI\n";
                    cout << "2. Decision Tree AI\n";
                    cout << "3. Human Player\n";
                    cout << "Enter your choice: ";
                    int type;
                    cin >> type;

                    playerPtr[0].reset(new UltimateHumanPlayer("Player 1", 'X'));

                    switch (type) {
                        case 1:
                            playerPtr[1].reset(new UltimateRandomPlayer('O'));
                            break;
                        case 2:
                            playerPtr[1].reset(new UltimateDecisionTreePlayer('O'));
                            break;
                        case 3:
                            playerPtr[1].reset(new UltimateHumanPlayer("Player 2", 'O'));
                            break;
                        default:
                            cout << "Invalid choice. Defaulting to Human vs Human.\n";
                            playerPtr[1].reset(new UltimateHumanPlayer("Player 2", 'O'));
                            break;
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
                    cout << "3. Decision Tree AI\n";
                    cin >> choice;

                    switch (choice) {
                        case 1:
                            players[0] = new X_O_Player<char>(playerXName, 'S');
                            break;
                        case 2:
                            players[0] = new X_O_Random_Player<char>('S');
                            break;
                        case 3:
                            players[0] = new X_O_DecisionTreePlayer<char>('S');
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
                    cout << "3. Decision Tree AI\n";
                    cin >> choice;

                    switch (choice) {
                        case 1:
                            players[1] = new X_O_Player<char>(player2Name, 'U');
                            break;
                        case 2:
                            players[1] = new X_O_Random_Player<char>('U');
                            break;
                        case 3:
                            players[1] = new X_O_DecisionTreePlayer<char>('U');
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
                    break;

                    return 0;
                }
            }


                default:
                    cout << "Invalid choice. Please try again.\n";
                continue;
            }


                if (choice >= 1 && choice <= 8) {
                    playerPtr[0]->setBoard(boardPtr.get());
                    playerPtr[1]->setBoard(boardPtr.get());
                    if (choice != 9) {
                        int x, y;
                        if (choice == 1) boardPtr->display_board();
                        if (choice == 2) boardPtr->display_board();
                        if (choice == 3) boardPtr->display_board();
                        if (choice == 4) boardPtr->display_board();
                        if (choice == 5) boardPtr->display_board();
                        if (choice == 6) boardPtr->display_board();
                        if (choice == 7) boardPtr->display_board();
                        if (choice == 8) boardPtr->display_board();

                        while (!boardPtr->game_is_over()) {
                            for (int i: {0, 1}) {
                                if (choice == 5 && dynamic_cast<NumericalHumanPlayer *>(playerPtr[i].get())) {
                                    int c = playerPtr[i]->getsymbol();
                                    playerPtr[i]->getmove(x, y);
                                    if (!boardPtr->update_board(x, y, c)) {
                                        i--;
                                        continue;
                                    }
                                } else {
                                    playerPtr[i]->getmove(x, y);
                                    while (!boardPtr->update_board(x, y, playerPtr[i]->getsymbol())) {
                                        playerPtr[i]->getmove(x, y);

                                    }
                                }

                                if (dynamic_cast<MisereDecisionTreePlayer *>(playerPtr[i].get()) ||
                                    dynamic_cast<NumericalDecisionTreePlayer *>(playerPtr[i].get()) ||
                                    dynamic_cast<PyramicDecisionTreePlayer *>(playerPtr[i].get())) {
                                    cout << playerPtr[i]->getname() << " moves: " << "(" << x << ", " << y << ")\n";
                                }
                                if (choice == 1) boardPtr->display_board();
                                if (choice == 2) boardPtr->display_board();
                                if (choice == 3) boardPtr->display_board();
                                if (choice == 4) boardPtr->display_board();
                                if (choice == 5) boardPtr->display_board();
                                if (choice == 6) boardPtr->display_board();
                                if (choice == 7) boardPtr->display_board();
                                if (choice == 8) boardPtr->display_board();
                                if (boardPtr->is_win()) {
                                    if (choice == 6)
                                        cout << playerPtr[i]->getname() << " loses!\n";
                                    else
                                        cout << playerPtr[i]->getname() << " wins!\n";
                                    goto end_game;
                                }
                                if (boardPtr->is_draw()) {
                                    cout << "Draw!\n";
                                    goto end_game;
                                }
                            }
                        }
                        end_game:;
                    }
                }

        }
        return 0;
}
