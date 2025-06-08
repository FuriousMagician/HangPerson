// ********************************************************
// Title: Design Project 4
// Course: Computational Problem Solving
// Developer: James Musonda
// ********************************************************

#include "hangPerson.h"

using namespace std;

int main() {
	int wrongGuesses = 0;
	char Guess = ' ';
	bool validInput = false;
	bool found = false;
	bool finishedGame = false;
	srand(time(NULL)); // Used for selectWord()
	string Answer = selectWord();
	string displayAnswer = string(Answer.length(), '*');
	ofstream Output("results_1.txt"); //Text file for results
	vector<char> Guesses;		      //Previous guesses

	if (!Output.is_open()) {
		cout << "Results file not found." << endl;
		exit(1);
	}
	Output << "The chosen word is " << Answer << ".\n\n";

	while(!finishedGame) {
		display(wrongGuesses, Answer, Guesses, displayAnswer);

		validInput = false;
		finishedGame = false;
		found = false;

		while (!validInput) {
			cout << "Enter your guess: ";
			cin >> Guess;

			if (cin.fail()) {
				cin.clear();
				cin.ignore(10000, '\n');
				cout << "Invalid input.\n";
				continue;
			}

			if (isalpha(Guess)) Guess = tolower(Guess);

			if (!islower(Guess)) {
				cout << "\nPlease enter a letter.\n";
				continue;
			}

			if (find(Guesses.begin(), Guesses.end(), Guess) != Guesses.end()) {
				cout << "\nAlready guessed that letter. Try again.\n";
				continue;
			}
			validInput = true;
		} //while(validInput)

		Guesses.push_back(Guess);

		for (int t = 0; t < Answer.length(); t++) {
			if (Answer[t] == Guess) {
				displayAnswer[t] = Guess;
				found = true;
			}
		}

		if (!found) { wrongGuesses++; }

		if (displayAnswer == Answer || wrongGuesses > 7) {
			finishedGame = true;
		}

		recordResults(wrongGuesses, Answer, Guess, found, finishedGame, Output);
	} // while (!finishedGame)
	
	display(wrongGuesses, Answer, Guesses, displayAnswer);
	cout << "Game over! The word was: " << Answer << "\n\n";

	system("pause");
	return 0;
}