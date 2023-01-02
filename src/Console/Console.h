/*!
 * @file Console.h
 * @brief Contains Console io commands
 *
 *  Created on: 2022-12-26
 *      Author: Moritz Geßner
 */

#pragma once

#include "../Manipulator.h"


class Console
{
private:
	Manipulator& manip;

	const unsigned int CONSOLE_WIDTH = 93; // Change to your liking
	const int KEY_ENTER = 10;
	const int KEY_TAB = 9;
	const int KEY_ESCAPE = 27; // Will be called for arrow keys etc
	const int KEY_BACKSPACE = 127;
	const int KEY_DELETE = 126;
	const int KEY_UP = 65;
	const int KEY_DOWN = 66;
	const int KEY_RIGHT = 67;
	const int KEY_LEFT = 68;
	const int KEY_ESCAPE2 = 91; // This seems to be called to move the cursor once to the left in escape sequences
	const int KEY_POS1 = 72;
	const int KEY_END = 70;
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
	const int KEY_HAT = 94;

	void PrintTermToConsole(Term*& t);
	void PrintLatexToConsole(Term*& t);
	int PrintTreeToConsole(Term*& t, bool withPtr=false); // return maxDepth
	int Input(char& key); // return 3 to exit InteractiveInput, -1 to exit program, 1 if input is not readable, 0 otherwise
	int Latex(Term*& t);
	int InteractiveInput();
	// Keys:
	int PressUpArrow();
	int PressDownArrow();
	int PressRightArrow();
	int PressLeftArrow();
	int PressPos1();
	int PressEnd();
	int PressNumber(int digit);
	int PressLetter(char ch);
	int PressEnter();
	int PressTab();
	int PressBackspace();
	int PressDelete();
	int PressPlus();
	int PressMinus();
	int PressKomma();
	int PressDecimal();
	int PressAsterisk();
	int PressSlash();
	int PressHat();
public:
	//Console(IO& _io);
	Console(Manipulator& _manip);
	void ShellLoop();
};
