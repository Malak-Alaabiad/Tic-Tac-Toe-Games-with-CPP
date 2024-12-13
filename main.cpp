#include <iostream>
#include <vector>
#include <memory>
#include <random>
#include "BoardGame_Classes.h"
using namespace std;
#include "PyramicTicTacToe.cpp"
#include "FourInRow.cpp"
#include "TicTacToe5x5.cpp"
#include "WordTicTacToe.cpp"
#include "NumericalTicTacToe.cpp"
#include "MisereTicTacToe.cpp"
#include "TicTacToe4x4.cpp"
#include "UltimateTicTacToe.cpp"
#include "SUSGame.cpp"

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
                if(type == 1){
                    playerPtr[0] = new PyramicHumanPlayer("Player 1", 'X');
                    playerPtr[1] = new PyramicRandomPlayer('O');
                }else{
                    playerPtr[0] = new PyramicHumanPlayer("Player 1", 'X');
                    playerPtr[1] = new PyramicHumanPlayer("Player 2", 'O');
                }
                break;
            }
            case 2: {
                boardPtr = new FourInARowBoard();
                cout << "\nPlay against AI (1) or Human (2)?: ";
                int type;
                cin >> type;
                if(type == 1){
                    playerPtr[0] = new FourInARowHumanPlayer("Player 1", 'X');
                    playerPtr[1] = new FourInARowRandomPlayer('O');
                }else{
                    playerPtr[0] = new FourInARowHumanPlayer("Player 1", 'X');
                    playerPtr[1] = new FourInARowHumanPlayer("Player 2", 'O');
                }
                break;
            }
            case 3: {
                boardPtr = new FiveByFiveBoard();
                cout << "\nPlay against AI (1) or Human (2)?: ";
                int type;
                cin >> type;
                if(type == 1){
                    playerPtr[0] = new FiveByFiveHumanPlayer("Player 1", 'X');
                    playerPtr[1] = new FiveByFiveRandomPlayer('O');
                }else{
                    playerPtr[0] = new FiveByFiveHumanPlayer("Player 1", 'X');
                    playerPtr[1] = new FiveByFiveHumanPlayer("Player 2", 'O');
                }
                break;
            }
            case 4: {
                try{
                    boardPtr = new WordBoard();
                    cout << "\nPlay against AI (1) or Human (2)?: ";
                    int type;
                    cin >> type;
                    if(type == 1){
                        playerPtr[0] = new WordHumanPlayer("Player 1", ' ');
                        playerPtr[1] = new WordRandomPlayer(' ');
                    }else{
                        playerPtr[0] = new WordHumanPlayer("Player 1", ' ');
                        playerPtr[1] = new WordHumanPlayer("Player 2", ' ');
                    }
                }catch(const std::runtime_error& e){
                    cerr << e.what() << endl;
                    continue;
                }
                break;
            }
            case 5: {
                boardPtr = reinterpret_cast<Board<char> *>(new NumericalBoard());
                cout << "\nPlay against AI (1) or Human (2)?: ";
                int type;
                cin >> type;
                if(type == 1){
                    playerPtr[0] = reinterpret_cast<Player<char> *>(new NumericalHumanPlayer("Player 1", 1));
                    playerPtr[1] = reinterpret_cast<Player<char> *>(new NumericalRandomPlayer(2));
                }else{
                    playerPtr[0] = reinterpret_cast<Player<char> *>(new NumericalHumanPlayer("Player 1", 1));
                    playerPtr[1] = reinterpret_cast<Player<char> *>(new NumericalHumanPlayer("Player 2", 2));
                }
                break;
            }
            case 6: {
                boardPtr = new MisereBoard();
                cout << "\nPlay against AI (1) or Human (2)?: ";
                int type;
                cin >> type;
                if(type == 1){
                    playerPtr[0] = new MisereHumanPlayer("Player 1", 'X');
                    playerPtr[1] = new MisereRandomPlayer('O');
                }else{
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
                if(type == 1){
                    playerPtr[0] = new FourByFourHumanPlayer("Player 1", 'X');
                    playerPtr[1] = new FourByFourRandomPlayer('O');
                }else{
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
                if(type == 1){
                    playerPtr[0] = new UltimateHumanPlayer("Player 1", 'X');
                    playerPtr[1] = new UltimateRandomPlayer('O');
                }else{
                    playerPtr[0] = new UltimateHumanPlayer("Player 1", 'X');
                    playerPtr[1] = new UltimateHumanPlayer("Player 2", 'O');
                }
                break;
            }
            case 9: {
                boardPtr = new SUSBoard();
                cout << "\nPlay against AI (1) or Human (2)?: ";
                int type;
                cin >> type;
                if(type == 1){
                    playerPtr[0] = new SUSHumanPlayer("Player 1", ' ');
                    playerPtr[1] = new SUSRandomPlayer(' ');
                }else{
                    playerPtr[0] = new SUSHumanPlayer("Player 1", ' ');
                    playerPtr[1] = new SUSHumanPlayer("Player 2", ' ');
                }
                break;
            }

            default:
                cout << "Invalid choice. Please try again.\n";
                continue;
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