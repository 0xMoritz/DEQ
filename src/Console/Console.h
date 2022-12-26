/*!
 * @file Console.h
 * @brief Contains Console io commands
 *
 *  Created on: Dec 26, 2022
 *      Author: Moritz Geßner
 */

#pragma once

#include "../IO.h"


class Console
{
private:
	IO& io;

	const unsigned int CONSOLE_WIDTH = 93; // Change to your liking
	const int KEY_ENTER = 10;
	const int KEY_ESCAPE = 27; // Will be called for arrow keys etc
	const int KEY_BACKSPACE = 127;
	const int KEY_DELETE = 126;
	const int KEY_UP = 65;
	const int KEY_DOWN = 66;
	const int KEY_RIGHT = 67;
	const int KEY_LEFT = 68;
	const int KEY_MOVELEFT = 91;
	const int KEY_EOF = 4;
	const int KEYS_LOWER_CASE_LETTERS_START = 97;
	const int KEYS_LOWER_CASE_LETTERS_END = 122;
	const int KEYS_UPPER_CASE_LETTERS_START = 65;
	const int KEYS_UPPER_CASE_LETTERS_END = 90;
	const int KEY_NUMBER_START = 48;
	const int KEY_NUMBER_END = 57;
	const int KEY_PLUS = 43;
	const int KEY_MINUS = 45;
	const int KEY_ASTERISK = 42;
	const int KEY_SLASH = 47;
	const int KEY_DECIMAL = 46;
	const int KEY_KOMMA = 44;

	void PrintTermToConsole(Term*& t);
	void PrintLatexToConsole(Term*& t);
	int PrintTreeToConsole(Term*& t); // return maxDepth
	int Input(Term*& t, char& key); // return 3 to exit InteractiveInput, -1 to exit program, 1 if input is not readable, 0 otherwise
	int Latex(Term*& t);
	int InteractiveInput(Term*& t);
	// Keys:
	int PressUpArrow(Term*& t);
	int PressDownArrow(Term*& t);
	int PressRightArrow(Term*& t);
	int PressLeftArrow(Term*& t);
	int PressNumber(Term*& t, int digit);
	int PressLetter(Term*& t, char ch);
	int PressEnter(Term*& t);
	int PressBackspace(Term*& t);
	int PressDelete(Term*& t);
	int PressPlus(Term*& t);
	int PressMinus(Term*& t);
	int PressKomma(Term*& t);
	int PressDecimal(Term*& t);
	int PressAsterisk(Term*& t);
	int PressSlash(Term*& t);
public:
	//Console(IO& _io);
	Console(IO& _io);
	void ShellLoop();
};
