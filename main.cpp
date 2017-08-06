/*
This is console executable
*/

#include <iostream>
#include <string>
#include "FBullCowGame.h"
using FText = std::string;

void PrintIntro();
void PlayGame();
FText GetValidGuess();
void PrintGuess(FText Guess);
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame;

//the entry point for application
int main()
{
	bool bPlayAgain = false;
	do {
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} while (bPlayAgain);
	return 0;
}

void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();
	//loop for the no of turns
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{

	//for (int32 count = 1; count <= MaxTries; count++) {
		FText Guess = GetValidGuess();

		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		BCGame.CheckGameWon(BullCowCount);

		std::cout << "Bulls : " << BullCowCount.Bulls << "  &&  ";
		std::cout << "Cows : " << BullCowCount.Cows << std::endl;

		//PrintGuess(Guess);
		std::cout << std::endl;
	}

	PrintGameSummary();
}

//introduce the game
void PrintIntro() {

	std::cout << "\n\nWelcome to Bulls and Cows, a fun word game.\n";
	std::cout << std::endl;
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;

	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I am thinking of?";
	std::cout << std::endl;
	return;
}

//Get a guess from player
FText GetValidGuess() {
	EWordStatus Status = EWordStatus::INVALID;
	FText Guess = "";
	do
	{
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries() << ". ";
		std::cout << "Enter your guess : ";

		getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case NOT_ISOGRAM:
			std::cout << "Please enter a word without repeating letters.\n\n";
			break;
		case INVALID_LENGTH:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case NOT_LOWERCASE:
			std::cout << "Please enter all lowercase letters.\n\n";
			break;
		default:
			break;
		}
	} while (Status != EWordStatus::OK);

	return Guess;
}

void PrintGuess(FText Guess) {
	//Repeat the guess
	std::cout << "Your guess was : " << Guess;
	std::cout << std::endl;
}

void PrintGameSummary() {
	if (BCGame.IsGameWon())
	{
		std::cout << "Well Done!!!" << std::endl;
	}
	else
	{
		std::cout << "Better luck next time." << std::endl;
	}
}

bool AskToPlayAgain() {
	std::cout << "Do you want to play again (y/n) : ";

	FText Response = "";
	getline(std::cin, Response);

	return (Response[0] == 'y') || (Response[0] == 'Y');
}