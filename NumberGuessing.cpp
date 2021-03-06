// A simple numbers guessing game

// include required headers
#include <iostream>
#include <string>

// use the std namespace so we don't have to type in std:: every time we use a basic function
using namespace std;

// constants, a user inputted number must be equal to or larger than the minimum and less than or equal to the maximum guess
const int minGuess = 1;
const int maxGuess = 1000000;

// the maximum number of guesses it should take to hit the player's number
// as of right now I don't have an algorithm to determine this, so it'd need to be scaled along
// with the ranges from above
const int maxGuessAmount = 20;

// same as the constants, except the range grows closer with every player guess
int minRange = minGuess;
int maxRange = maxGuess;

// formulates a new guess
// guess: the old guess to base off of
// larger: whether or not the number is larger or smaller than the guess
int formulateGuess(int guess, bool larger)
{
	if (larger)
	{
		// if the number is larger, then the minimum it could be is the guess + 1
		minRange = guess + 1;
	}
	else
	{
		// if the number is smaller, then the number it could be is the guess - 1
		maxRange = guess - 1;
	}

	// return the mid-point of the range
	return ((maxRange - minRange) / 2) + minRange;
}

// essentially resets all the values if the player wishes to re-play
bool replay()
{
	system("CLS");

	cout << "Would you like to play again? Y = continue/anything else = no" << endl;

	char i;

	cin >> i;

	cin.ignore();

	// if input is yes, reset global variables
	if (i == 'Y' || i == 'y')
	{
		minRange = minGuess;
		maxRange = maxGuess;

		return true;
	}

	// player declined to continue
	return false;
}

// this is the function that is executed upon the program's launch
int main()
{
	// while true this program will continue to loop through it's main functions
	bool running = true;

	// the number we're guessing the player chose
	int guess = maxGuess / 2;

	// the number of turns it's taking us to guess the number
	int turns = 1;

	// game loop
	while (running)
	{
		// clears the console
		system("CLS");

		// this is my cheap attempt into created a welcome message whenever a game starts up
		// if the turn counter is at 1 we know the game has just begun and we can display the rules of the game
		if (turns == 1)
		{
			cout << "Choose a number no smaller than " << minGuess << " and no larger than " << maxGuess << "." << endl
				<< "this program will then attempt to guess your number in under " << maxGuessAmount << " turns using your input" << endl
				<< "Press Enter to begin";

			cin.ignore();

			system("CLS");
		}

		// output the number of turns left
		// also output our guess
		cout << "I have " << (maxGuessAmount - turns) << " guesses left" << endl
			<< "Is your number: " << guess << "?" << endl
			<< "Y = yes | G = my number is greater | L = my number is smaller" << endl;


		// obtain player input
		char input;

		cin >> input;

		// while the player doesn't have a valid input
		while (input != 'Y' && input != 'y' && input != 'G' && input != 'g' && input != 'L' && input != 'l')
		{
			cout << "Please enter a valid input!" << endl;
			cin >> input;
		}

		// ignore the keyboard enter we just recorded for the player input
		cin.ignore();

		if (input == 'Y' || input == 'y') // if we agree that the number guessed is correct
		{
			// if the guess is correct, tell them how many turns we guessed in
			// then prompt them to press Enter to continue
			cout << "I have guessed your number in " << turns << " turns!" << endl
				<< "Press Enter to continue" << endl;
			cin.ignore();

			// reset the game, or exit if the player so chooses
			running = replay();
			guess = maxGuess / 2;
			turns = 1;
		}
		else if (minRange == maxRange) // if we decline with the guess but it's the only number in our range
		{
			// the player has somewhere lied to us during our guessing game
			// expose them for their lies and then prompt them to press Enter to continue
			cout << "Your number has to be " << guess << " or you cheated." << endl
				<< "Press Enter to continue" << endl;
			cin.ignore();

			// reset the game, or exit if the player so chooses
			// the AI has no feelings and doesn't mind that the player is a liar
			// and as a result? The AI will happily play another game
			running = replay();
			guess = maxGuess / 2;
			turns = 1;
		}
		else if (turns == maxGuessAmount) // when we run out of turns
		{
			// the player has won congradulate them and prompt them to press Enter to continue
			cout << "You win! I could not guess your number in " << maxGuessAmount << " guesses!" << endl
				<< "Press Enter to continue" << endl;
			cin.ignore();

			// reset the game, or exit if the player so chooses
			running = replay();
			guess = maxGuess / 2;
			turns = 1;
		}
		else
		{
			// if we haven't guessed, we need to formulate a new guess
			guess = formulateGuess(guess, input == 'G' || input == 'g');

			// and of course with a new guess we'll need to take another turn
			turns++;
		}
	}

	// finally we return that we exited successfully
	return EXIT_SUCCESS;
}

