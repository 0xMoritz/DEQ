#include "Console.h"


using namespace std;

Console::Console(IO& _io) : io(_io)
{

}
void Console::PrintTermToConsole(Term*& t)
{
	cout << t->Print() << endl;
}
void Console::PrintLatexToConsole(Term*& t)
{
	cout << t->Tex() << endl;
}

int Console::PrintTreeToConsole(Term*& t) // return maxDepth
{
	StringTree tree{};
	int maxDepth = 0;
	t->Tree(tree, maxDepth);
	cout << tree.Write(maxDepth) << endl;
	return maxDepth;
}


int Console::Input(Term*& t, char& key) // return 3 to exit InteractiveInput, -1 to exit program, 1 if input is not readable, 0 otherwise
{
	if (read(STDIN_FILENO, &key, 1) != 1)
	{
		throw (string)("Read Error or EOF");
	}
	if (key == KEY_EOF)
	{
		throw (string)("Control-D or EOF");
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
			if (read(STDIN_FILENO, &key, 1) == 1 && key == KEY_MOVELEFT)
			{
				if (read(STDIN_FILENO, &key, 1) == 1)
				{
					if (key == KEY_UP)
						PressUpArrow(t);
					else if (key == KEY_RIGHT)
						PressRightArrow(t);
					else if (key == KEY_LEFT)
						PressLeftArrow(t);
					else if (key == KEY_DOWN)
						PressDownArrow(t);
					else
						return 1;
				}
				else
				{
					throw ((string)"Noticed Escape sequence but could not decipher " + static_cast<char>(key));
				}
			}
			else
			{
				throw ((string)"Noticed Escape sequence but could not decipher " + key);
			}
		}
		else if (selret == -1)
		{
			throw ((string)"Damn, How did you do it? I didn't imagine this error could ever be thrown so I didn't bother giving it a name");
		}
		else
		{
			return 3;
		}
	}
	else  // no escape sequence
	{
		if (key == KEY_ENTER)
		{
			return PressEnter(t);
		}
		else if (key == KEY_BACKSPACE)
		{
			return PressBackspace(t);
		}
		else if (key == KEY_DELETE)
		{
			return PressDelete(t);
		}
		else if (KEY_NUMBER_START <= key && key <= KEY_NUMBER_END)
		{
			return PressNumber(t, key-KEY_NUMBER_START);
		}
		else if ((KEYS_LOWER_CASE_LETTERS_START <= key && key <= KEYS_LOWER_CASE_LETTERS_END)
			|| (KEYS_UPPER_CASE_LETTERS_START <= key && key <= KEYS_UPPER_CASE_LETTERS_END)) // Uppercase or Lowercase letter
		{
			return PressLetter(t, (char)key);
		}
		else if (key == KEY_PLUS)
		{
			return PressPlus(t);
		}
		else if (key == KEY_MINUS)
		{
			return PressMinus(t);
		}
		else if (key == KEY_KOMMA)
		{
			return PressKomma(t);
		}
		else if (key == KEY_DECIMAL)
		{
			return PressDecimal(t);
		}
		else if (key == KEY_ASTERISK)
		{
			return PressAsterisk(t);
		}
		else if (key == KEY_SLASH)
		{
			return PressSlash(t);
		}
		else
		{
			throw ((string)"Illegal input: " + to_string(static_cast<int>(key)));
		}
	}
	return key;
}


// Print Latex Equation
int Console::Latex(Term*& t)
{
	string eq = t->Tex();
	// Write only the equation for GUI
	{
		string filename = "eq";
		FilePrinter printer(filename);
		printer.Write(eq);
		printer.CloseFile();
	}

	// Write to standalone latex file and execute pdfLatex
	string compilePdfLatex =
	"\\documentclass{standalone}\n"
	"\\begin{document}\n"
		"\t$\\displaystyle\n\t"
		+ eq +
		"\n\t$\n"
	"\\end{document}\n";
	string filename = "eq.tex";
	FilePrinter printer(filename);
	printer.Write(compilePdfLatex);
	printer.CloseFile();

	// generate pdf
	string pdfLatexCommand = "cd " + printer.GetOutputPath() + " && pdflatex " + filename;
	cout << pdfLatexCommand << endl << endl;
	int pdfLatexOutput = system(pdfLatexCommand.c_str());
	cout << system("\n") << endl;
	cout << "pdfLatex returned " << pdfLatexOutput << endl << endl;

	// Open pdf
	string openPDFCommand = "okular --unique " + printer.GetOutputPath() + "/" + "eq.pdf &";
	cout << "okular returned" << system(openPDFCommand.c_str()) << endl << endl;
	return 0;
}

// Interactive equation with instant feedback
int Console::InteractiveInput(Term*& t)
{
	// put terminal into non-canonical mode
	struct termios oldTermios;
	struct termios newTermios;
	int fd = 0;	  // stdin
	tcgetattr(fd, &oldTermios);
	newTermios = oldTermios;
	newTermios.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(fd, TCSANOW, &newTermios);

	int res = 0;
	int depth = 0;
	char key;
	while (1)
	{
		try
		{
			int stat = Input(t, key);
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

				// Print status
				PrintTermToConsole(t);
				depth = PrintTreeToConsole(t);
				//cout << (int)key << endl;

				// Debug Line
				if (io.debugText.length() > CONSOLE_WIDTH)
					io.debugText = io.debugText.substr(io.debugText.length() - CONSOLE_WIDTH, CONSOLE_WIDTH); // Restrict length to prevent overflow
				cout << string(CONSOLE_WIDTH - io.debugText.length(), ' ') << io.debugText << endl;
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
	Term* t = new Cursor(nullptr);
	Cursor::SetActive(dynamic_cast<Cursor*>(t));

	while (1)
	{
		string in;
		cout << "> ";
		cin >> in;
		if (in == "i" || in == "Interactive")
		{
			cout << "Entering Interactive input" << endl << endl;
			int out = InteractiveInput(t);
			if (out != 0)
				break;
		}
		else if (in == "l" || in == "Latex")
		{
			Latex(t);
		}
		else if (in == "t" || in == "Tree")
		{
			PrintTreeToConsole(t);
		}
		else if (in == "x" || in == "q" || in == "Quit" || in == "Exit")
		{
			break;
		}
		else if (in == "p" || in == "Print")
		{
			cout << t->Print() << endl;
		}
	}
}

// Keys
int Console::PressUpArrow(Term*& t)
{
	throw (string)"No Action set for 'up arrow'";
	return 0;
}
int Console::PressDownArrow(Term*& t)
{
	throw (string)"No Action set for 'down arrow'";
	return 0;
}
int Console::PressRightArrow(Term*& t)
{
	throw (string)"No Action set for 'right arrow'";
	return 0;
}
int Console::PressLeftArrow(Term*& t)
{
	throw (string)"No Action set for 'left arrow'";
	return 0;
}
int Console::PressNumber(Term*& t, int digit)
{
	io.InsertDigit(t, digit);
	return 0;
}
int Console::PressLetter(Term*& t, char ch)
{
	throw (string)"No Action set for '" + ch + "'";
	return 0;
}
int Console::PressEnter(Term*& t)
{
	PrintLatexToConsole(t);
	return 2;
}
int Console::PressBackspace(Term*& t)
{
	io.Backspace(t);
	return 0;
}
int Console::PressDelete(Term*& t)
{
	io.Delete(t);
	return 2;
}
int Console::PressPlus(Term*& t)
{
	throw (string)"No Action set for '+'";
	return 0;
}
int Console::PressMinus(Term*& t)
{
	throw (string)"No Action set for '-'";
	return 0;
}
int Console::PressKomma(Term*& t)
{
	throw (string)"No Action set for ','";
	return 0;
}
int Console::PressDecimal(Term*& t)
{
	throw (string)"No Action set for '.'";
	return 0;
}
int Console::PressAsterisk(Term*& t)
{
	throw (string)"No Action set for '*'";
	return 0;
}
int Console::PressSlash(Term*& t)
{
	throw (string)"No Action set for '/'";
	return 0;
}
