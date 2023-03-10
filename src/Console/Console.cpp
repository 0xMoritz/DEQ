#include "Console.h"


using namespace std;

Console::Console(Manipulator& _manip) : manip(_manip)
{

}
void Console::PrintTermToConsole(Term*& t)
{
	cout << t->Print() << endl;
}
void Console::PrintLatexToConsole(Term*& t)
{
	cout << t->GetTex() << endl;
}

int Console::PrintTreeToConsole(Term*& t, bool withPtr) // return maxDepth
{
	StringTree tree{};
	int maxDepth = 0;
	t->Tree(tree, maxDepth, withPtr);
	cout << tree.Write(maxDepth) << endl;
	return maxDepth;
}


int Console::Input(char& key) // return 3 to exit InteractiveInput, -1 to exit program, 1 if input is not readable, 0 otherwise
{

	if (read(STDIN_FILENO, &key, 1) != 1)
	{
		throw (string)"Read Error or EOF";
	}
	if (key == KEY_EOF)
	{
		throw (string)"Control-D or EOF";
	}

	// check for ESC seq
	if (key == KEY_ESCAPE)
	{
		// idk, this is c-magic to me...
		// https://stackoverflow.com/questions/48039759/how-to-distinguish-between-escape-and-escape-sequence
		fd_set set;
		struct timeval timeout;
		FD_ZERO(&set);
		FD_SET(STDIN_FILENO, &set);
		timeout.tv_sec = 0;
		timeout.tv_usec = 0;
		int selret = select(1, &set, NULL, NULL, &timeout);
		if (selret == 1) // Sequence
		{
			if (read(STDIN_FILENO, &key, 1) == 1 && key == KEY_ESCAPE2)
			{
				if (read(STDIN_FILENO, &key, 1) == 1)
				{
					if (key == KEY_UP)
						return PressUpArrow();
					else if (key == KEY_RIGHT)
						return PressRightArrow();
					else if (key == KEY_LEFT)
						return PressLeftArrow();
					else if (key == KEY_DOWN)
						return PressDownArrow();
					else if (key == KEY_POS1)
						return PressPos1();
					else if (key == KEY_END)
						return PressEnd();
					else
						return 1;
				}
				else
				{
					throw (string)"Noticed Escape sequence but could not decipher " + static_cast<char>(key);
				}
			}
			else
			{
				throw (string)"Noticed Escape sequence but could not decipher " + key;
			}
		}
		else if (selret == -1)
		{
			throw (string)"Damn, How did you do it? I didn't imagine this error could ever be thrown so I didn't bother giving it a name";
		}
		else
		{
			// Pressing actual Escape key
			return 3;
		}
	}
	else  // no escape sequence
	{
		if (key == KEY_ENTER)
			return PressEnter();
		else if (key == KEY_TAB)
			return PressTab();
		else if (key == KEY_BACKSPACE)
			return PressBackspace();
		else if (key == KEY_DELETE)
			return PressDel();
		else if (KEY_NUMBER_START <= key && key <= KEY_NUMBER_END)
			return PressNumber(key-KEY_NUMBER_START);
		else if ((KEYS_LOWER_CASE_LETTERS_START <= key && key <= KEYS_LOWER_CASE_LETTERS_END)
			|| (KEYS_UPPER_CASE_LETTERS_START <= key && key <= KEYS_UPPER_CASE_LETTERS_END)) // Uppercase or Lowercase letter
		{
			return PressLetter((char)key);
		}
		else if (key == KEY_PLUS)
			return PressPlus();
		else if (key == KEY_MINUS)
			return PressMinus();
		else if (key == KEY_KOMMA)
			return PressKomma();
		else if (key == KEY_DECIMAL)
			return PressDecimal();
		else if (key == KEY_ASTERISK)
			return PressAsterisk();
		else if (key == KEY_SLASH)
			return PressSlash();
		else if (key == KEY_HAT)
			return PressHat();
		else
		{
			throw ((string)"Illegal input: " + to_string(static_cast<int>(key)));
		}
	}
	return 1;
}

// Interactive equation with instant feedback
int Console::InteractiveInput()
{
	// put terminal into non-canonical mode
	struct termios oldTermios;
	struct termios newTermios;
	int fd = 0;	  // stdin
	tcgetattr(fd, &oldTermios);
	newTermios = oldTermios;
	newTermios.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(fd, TCSANOW, &newTermios);

	PrintTermToConsole(manip.GetrootTerm());
	int depth = PrintTreeToConsole(manip.GetrootTerm());
	int res = 0;
	char key;
	while (1)
	{
		try
		{
			int stat = Input(key);
			if (stat == 3)
			{
				res = 0;
				break;
			}
			else if (stat == 2)
			{
				continue;
			}
			else if (stat == -1)
			{
				res = -1;
				break;
			}
			// Overwrite last tree
			else if (stat == 0)
			{
				for (int i = 0; i < depth+3; i++)
				{
					cout << "\033[A" << "\33[2K"; // Delete and move up
				}
				cout << "\b"; // Bring back cursor with \b

				// CheckConnections
				vector<Term*> errorTerms;
				bool areThereErrors = manip.CheckTermLinks(manip.GetrootTerm(), errorTerms);
				if (areThereErrors)
				{
					vector<Term*>::iterator errorIt = errorTerms.begin();
					manip.debugText += "[Error] Connection Check at " + Term::PtrAddress(*errorIt);
					for (errorIt++; errorIt != errorTerms.end(); errorIt++)
						manip.debugText += ", " + Term::PtrAddress(*errorIt);
					manip.debugText += ". ";
				};

				// Print status
				PrintTermToConsole(manip.GetrootTerm());
				depth = PrintTreeToConsole(manip.GetrootTerm());
				//cout << (int)key << endl;

				// Debug Line
				if (manip.debugText.length() > CONSOLE_WIDTH)
					manip.debugText = manip.debugText.substr(manip.debugText.length() - CONSOLE_WIDTH, CONSOLE_WIDTH); // Restrict length to prevent overflow
				cout << string(CONSOLE_WIDTH - manip.debugText.length(), ' ') << manip.debugText << endl;
				manip.debugText = ""; // Reset debug text
				//cout << "\b";
			}
		}
		catch (string err)
		{
			cerr << "[Error] " << err << endl;
			//return 1;
		}
	}

	// set terminal back to canonical
	tcsetattr(fd, TCSANOW, &oldTermios);
	return res;
}

// Standard Loop for manipulation
void Console::ShellLoop()
{
	Term*& rootTerm = manip.GetrootTerm();

	while (1)
	{
		string in;
		cout << "> ";
		cin >> in;
		if (in == "i" || in == "Interactive")
		{
			cout << "Entering Interactive input" << endl;
			int out = InteractiveInput();
			if (out != 0)
				break;
		}
		else if (in == "l" || in == "latex")
		{
			manip.Latex(manip.GetrootTerm());
		}
		else if (in == "t" || in == "tree")
		{
			PrintTreeToConsole(rootTerm);
		}
		else if (in == "pt" || in == "ptrTree")
		{
			PrintTreeToConsole(rootTerm, true);
		}
		else if (in == "x" || in == "q" || in == "quit" || in == "exit")
		{
			break;
		}
		else if (in == "p" || in == "Print")
		{
			cout << rootTerm->Print() << endl;
		}
		else if (in == "ptrrootTerm")
		{
			cout << Term::PtrAddress(rootTerm) << endl;
		}
		else if (in == "ptrCursor")
		{
			cout << Term::PtrAddress(Cursor::GetActive()) << endl;
		}
		else if (in == "ptrLeft")
		{
			cout << rootTerm->PtrAddress(manip.CursorLeft()) << endl;
		}
		else if (in == "ptrRight")
		{
			cout << rootTerm->PtrAddress(manip.CursorRight()) << endl;
		}
		else if (in == "nullptr")
		{
			cout << rootTerm->PtrAddress((Term*)nullptr) << endl;
		}
		else if (in == "RecursiveCleanUp")
		{
			manip.RecursiveCleanUp(rootTerm);
		}
		else if (in == "CheckLinks")
		{
			vector<Term*> errorTerms;
			bool areThereErrors = manip.CheckTermLinks(manip.GetrootTerm(), errorTerms);
			if (areThereErrors)
			{
				vector<Term*>::iterator errorIt = errorTerms.begin();
				manip.debugText += "[Error] Connection Check at " + Term::PtrAddress(*errorIt);
				for (errorIt++; errorIt != errorTerms.end(); errorIt++)
					manip.debugText += ", " + Term::PtrAddress(*errorIt);
				manip.debugText += ". ";
			}
			else
				cout << "No Errors found" << endl;
		}
	}
}

// Keys
int Console::PressUpArrow()
{
	throw (string)"No Action set for 'up arrow'";
	return 0;
}
int Console::PressDownArrow()
{
	throw (string)"No Action set for 'down arrow'";
	return 0;
}
int Console::PressRightArrow()
{
	manip.CursorMoveRight();
	return 0;
}
int Console::PressLeftArrow()
{
	manip.CursorMoveLeft();
	return 0;
}
int Console::PressPos1()
{
	throw (string)"No Action set for 'Pos1'";
	return 2;
}
int Console::PressEnd()
{
	throw (string)"No Action set for 'End'";
	return 2;
}
int Console::PressNumber(int digit)
{
	manip.InsertDigit(digit);
	return 0;
}
int Console::PressLetter(char ch)
{
	throw (string)"No Action set for '" + ch + "'";
	return 0;
}
int Console::PressEnter()
{
	PrintLatexToConsole(manip.GetrootTerm());
	return 2;
}
int Console::PressTab()
{
	throw (string)"No Action set for 'tab'";
	return 2;
}
int Console::PressBackspace()
{
	manip.Backspace();
	return 0;
}
int Console::PressDel()
{
	manip.Del();
	return 0;
}
int Console::PressPlus()
{
	manip.InsertAddition('+');
	return 0;
}
int Console::PressMinus()
{
	manip.InsertAddition('-');
	return 0;
}
int Console::PressKomma()
{
	throw (string)"No Action set for ','";
	return 0;
}
int Console::PressDecimal()
{
	throw (string)"No Action set for '.'";
	return 0;
}
int Console::PressAsterisk()
{
	throw (string)"No Action set for '*'";
	return 0;
}
int Console::PressSlash()
{
	throw (string)"No Action set for '/'";
	return 0;
}
int Console::PressHat()
{
	throw (string)"No Action set for '/'";
	return 0;
}
