// ***************************************************************************
//  CS 202 Word Ladder Program
//  Word Ladder
//  User enters two words.  if possible, a word ladder is made between the
//  Words such that any single step changes only one letter.

//  Example, path from "money" to "greed":
//	money coney covey cover coyer foyer fryer freer freed greed

// ***************************************************************************

#include <iostream>
#include <fstream>
#include <string>

#include "wordLadder.h"

using namespace std;


// ***************************************************************************

int main(int argc, char *argv[])
{
	wordLadder	myLadder;

// ------------------------------------------------------------------

	if (argc == 1) {
		cout << "Usage: ./ladder -w <wordFile>" << endl;
		return	EXIT_FAILURE;
	}

	if (argc != 3) {
		cout << "Error, must provide word file name." << endl;
		return	EXIT_FAILURE;
	}

	if(string(argv[1]) != "-w") {
		cout << "Error, invalid word file specifier." << endl;
		return	EXIT_FAILURE;
	}

	if (!myLadder.readDictionary(argv[2])) {
		cout << "Error, unable to read word file: " << argv[2] << endl;
		return	EXIT_FAILURE;
	}

// ------------------------------------------------------------------

	string	firstWord, lastWord;
	bool	isGood=false, doMore=true;

	cout << "CS 202 Word Ladder Program." << endl << endl;

	while (doMore) {
		cout << "--------------------" << endl;
		isGood = false;
		do {
			cout << "Enter First Word: ";
			getline(cin, firstWord);

			if (firstWord.empty()) {
				isGood = true;
				doMore = false;
				break;
			}

			if (!myLadder.validWord(firstWord))
				cout << "Error, first word is not in dictionary." << endl;
			else
				isGood = true;
		} while (!isGood);

		if (!doMore)
			break;

		isGood = false;
		do {
			cout << "Enter Second Word: ";
			getline(cin, lastWord);
			if (!myLadder.validWord(lastWord))
				cout << "Error, second word is not in dictionary." << endl;
			else
				isGood = true;
		} while (!isGood);

		if (myLadder.findLadder(firstWord, lastWord)) {
			cout << endl;
			cout << "Word Ladder: " << endl;
			myLadder.printLadder();
		} else
			cout << endl << "There is no path from " << firstWord << " to "
				<< lastWord << endl << endl;

		myLadder.resetLadder();
	}

// ------------------------------------------------------------------
//  All done...

	return	EXIT_SUCCESS;;
}

// ***************************************************************************


