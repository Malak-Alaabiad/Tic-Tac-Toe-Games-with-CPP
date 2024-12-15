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
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "BoardGame_Classes.h"
using namespace std;

class WordBoard : public Board<char> {
private:
    vector<string> dictionary;
    bool loadDictionary(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Error opening dictionary file.\n";
            return false;
        }
        string word;
        while (file >> word) {
            dictionary.push_back(word);
        }
        file.close();
        return true;
    }
    bool checkWord(const string& word) const {
        return find(dictionary.begin(), dictionary.end(), word) != dictionary.end();
    }

public:
    WordBoard() {
        rows = 3;
        columns = 3;
        board = new char* [rows];
        for(int i = 0; i < rows; i++){
            board[i] = new char[columns];
            for(int j = 0; j < columns; j++){
                board[i][j] = ' ';
            }
        }
        if(!loadDictionary("D:\\Assignment 1 OOP\\Games MM\\dic.txt")){
            throw runtime_error("Failed to load the dictionary");
        }
    }

    ~WordBoard() {
        for(int i=0; i<rows; i++){
            delete [] board[i];
        }
        delete [] board;
    }

    bool update_board(int x, int y, char symbol) override {
        if (x < 0 || x >= rows || y < 0 || y >= columns) return false;
        if (board[x][y] == ' ') {
            board[x][y] = symbol;
            n_moves++;
            return true;
        }
        return false;
    }

    void display_board() override {
        cout << "\n----------------------";
        for (int i = 0; i < rows; i++) {
            cout << "\n|";
            for (int j = 0; j < columns; j++) {
                if (board[i][j] == ' ') {
                    cout << "(" << i << "," << j << ")" << " |";
                } else {
                    cout << " " << board[i][j] << "   |";
                }
            }
            cout << "\n----------------------";
        }
        cout << endl;
    }

    bool is_win() override {
        //check for wins
        for (int i = 0; i < rows; ++i) {
            // Check horizontal
            if (board[i][0] != ' ' && board[i][1] != ' ' && board[i][2] != ' ') {
                string word;
                word += board[i][0];
                word += board[i][1];
                word += board[i][2];
                if(checkWord(word)) return true;
            }
            // Check vertical
            if (board[0][i] != ' ' && board[1][i] != ' ' && board[2][i] != ' ') {
                string word;
                word += board[0][i];
                word += board[1][i];
                word += board[2][i];
                if(checkWord(word)) return true;
            }
        }
        // Check diagonals
        if (board[0][0] != ' ' && board[1][1] != ' ' && board[2][2] != ' ') {
            string word;
            word += board[0][0];
            word += board[1][1];
            word += board[2][2];
            if(checkWord(word)) return true;
        }
        if (board[0][2] != ' ' && board[1][1] != ' ' && board[2][0] != ' ') {
            string word;
            word += board[0][2];
            word += board[1][1];
            word += board[2][0];
            if(checkWord(word)) return true;
        }
        return false;
    }
    bool is_draw() override {
        return (n_moves == rows*columns && !is_win());
    }

    bool game_is_over() override {
        return is_win() || is_draw();
    }
};

class WordRandomPlayer : public RandomPlayer<char> {
public:
    WordRandomPlayer(char symbol) : RandomPlayer<char>(symbol) {}
    void getmove(int& x, int& y) override{
        WordBoard* b = dynamic_cast<WordBoard*>(this->boardPtr);
        do{
            x = rand() % 3;
            y = rand() % 3;
        }while(b->board[x][y] != ' ');
    }
};

class WordHumanPlayer : public Player<char> {
public:
    WordHumanPlayer(string n, char symbol) : Player<char>(n, symbol) {}

    void getmove(int& x, int& y) override {
        cout << this->getname() << ", enter your move (row, column): ";
        cin >> x >> y;
        // Add validation for the input
        cout << "Enter your letter: ";
        char c;
        cin >> c;
        this->symbol = c;
    }
};