#pragma once

#include <iostream> 
#include <iomanip>
#include <string>
#include <vector>
#include <cctype>
#include <ctime>
#include <fstream>

using namespace std;

string selectWord() {
    vector<string> wordList;
    ifstream InputWord("words_1.txt");
    string answer;

    if (!InputWord.is_open()) {
        cout << "Words file not found." << endl;
        exit(4);
    }

    while (InputWord >> answer) {
        wordList.push_back(answer);
    }

    return wordList[rand() % wordList.size()];
} 

void display(int Incorrect, string Answer, vector<char> guessList, string displayAnswer) {
    system("cls"); //Clears the screen (super useful!)
    int a, b;
    char Board[8][8];

    for (a = 0; a < 8; ++a) {
        for (b = 1; b < 8; ++b) {
            Board[a][b] = ' ';
        }
        Board[a][0] = '|';
    }
    for (a = 1; a < 7; ++a) {
        Board[7][a] = '-';
    }
    Board[0][0] = '+';
    Board[7][0] = '+';

    if (Incorrect >= 0) {
        for (a = 1; a < 6; ++a) {
            Board[0][a] = '-';
        }
    }
    if (Incorrect >= 0) { Board[0][6] = '+'; }
    if (Incorrect >= 1) { Board[1][6] = '|'; }
    if (Incorrect >= 2) { Board[2][6] = 'O'; }
    if (Incorrect >= 3) { Board[3][6] = '|'; }
    if (Incorrect >= 4) { Board[3][5] = '-'; }
    if (Incorrect >= 5) { Board[3][7] = '-'; }
    if (Incorrect >= 6) { Board[4][6] = '|'; }
    if (Incorrect >= 7) { Board[5][5] = '['; }
    if (Incorrect >= 8) { Board[5][7] = ']'; }

    for (a = 0; a < 8; a++) {
        for (int b = 0; b < 8; b++) {
            cout << Board[a][b];
        }
        cout << endl;
    } //for

    for (int t = 0; t <= 2 * Answer.length(); t++) {
        if (t < Answer.length()) { cout << displayAnswer[t] << " "; }
        if (t == Answer.length()) { cout << endl; }
        if (t > Answer.length()) { cout << "_ "; }
    }
    // This is the for loop that displays the actual length of the
    // unknown word. 

    cout << "\n\nPrevious guesses: ";
    for (char t : guessList) { cout << t << " "; }
    cout << "\n\n";
}
// This should probably work better now :D

void recordResults(int wrongGuesses, string Answer, char Guess, bool found, bool finishedGame, ofstream& Output) {
    if (found) {
        Output << "The character " << Guess << " was found!\n";
    }
    else {
        Output << "The character " << Guess << " was not found! The error count is " << wrongGuesses << ".\n";
    }

    if (finishedGame) {
        if (wrongGuesses > 7) {
            Output << "\nThe user failed to find the word.";
        }
        else {
            Output << "\nThe user successfully found the word.";
        }
    } //finishedGame
} //recordResults