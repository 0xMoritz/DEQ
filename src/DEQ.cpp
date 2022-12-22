#include "DEQ.h"

const int CONSOLE_WIDTH = 93;

const int KEY_ENTER = 10;
const int KEY_ESCAPE = 27;
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

using namespace std;

string debugText = "";

// Static variable Initilization
string FilePrinter::outputPath{"latex/"};
Cursor* Cursor::activeCursor = nullptr;

void InsertDigit(Term*& t, int digit)
{
	Cursor* c = Cursor::GetActive();
	assert(c != nullptr);
	// Create the necessary object
	if (c->GetLeft() == nullptr)
	{
		// Always create the parent first
		Connect2* newParent = new Connect2(c->GetParent());
		if (c->GetParent() == nullptr)// Create new parent element, if the cursors parent is nullptr, than this will simply be handed over, however than we'll have to change the base Term element t
		{
			assert(t==c);
			t = static_cast<Term*>(newParent);
		}
		Number* newNumber = new Number(newParent);
		newParent->SetSub1(newNumber);
		c->SetParent(newParent);
		c->SetLeft(newNumber);
		newParent->SetSub2(c);
	}
	// Add the actual digit
	if (typeid(*c->GetLeft()) == typeid(Number))
	{
		dynamic_cast<Number*>(c->GetLeft())->AppendDigit(digit);
	}
	else
	{
		throw (string)"Could not add digit";
	}

}
// TODO: Change from number to raw format, which can be parsed into var, num, fct,...
void Backspace(Term*& t)
{
	Cursor* c = Cursor::GetActive();
	if (c->GetLeft() == nullptr)
		return;
	if (typeid(*c->GetLeft()) == typeid(Number))
	{
		Number* num = dynamic_cast<Number*>(c->GetLeft());
		num->BackspaceDigit();
		// if number becomes "empty"
		if (num->IsEmpty())
		{
			//TODO: implement a replace method.
			assert(typeid(*c->GetParent()) == typeid(Connect2));
			///TODO, attention with the hirarchy...
		}
	}
}

void Delete(Term*& t)
{
	throw (string)"Delete has not yet been implemented";
}



void PrintTermToConsole(Term*& t)
{
	cout << t->Print() << endl;
}

void PrintLatexToConsole(Term*& t)
{
	cout << t->Tex() << endl;
}

int PrintTreeToConsole(Term*& t) // return maxDepth
{
	StringTree tree{};
	int maxDepth = 0;
	t->Tree(tree, maxDepth);
	cout << tree.Write(maxDepth) << endl;
	return maxDepth;
}

int PressUpArrow(Term*& t)
{
	throw (string)"No Action set for 'up arrow'";
	return 0;
}
int PressDownArrow(Term*& t)
{
	throw (string)"No Action set for 'down arrow'";
	return 0;
}
int PressRightArrow(Term*& t)
{
	throw (string)"No Action set for 'right arrow'";
	return 0;
}
int PressLeftArrow(Term*& t)
{
	throw (string)"No Action set for 'left arrow'";
	return 0;
}
int PressNumber(Term*& t, int digit)
{
	InsertDigit(t, digit);
	return 0;
}
int PressLetter(Term*& t, char ch)
{
	throw (string)"No Action set for '" + ch + "'";
	return 0;
}
int PressEnter(Term*& t)
{
	PrintLatexToConsole(t);
	return 2;
}
int PressBackspace(Term*& t)
{
	Backspace(t);
	return 0;
}
int PressDelete(Term*& t)
{
	Delete(t);
	return 2;
}
int PressPlus(Term*& t)
{
	throw (string)"No Action set for '+'";
	return 0;
}
int PressMinus(Term*& t)
{
	throw (string)"No Action set for '-'";
	return 0;
}
int PressKomma(Term*& t)
{
	throw (string)"No Action set for ','";
	return 0;
}
int PressDecimal(Term*& t)
{
	throw (string)"No Action set for '.'";
	return 0;
}
int PressAsterisk(Term*& t)
{
	throw (string)"No Action set for '*'";
	return 0;
}
int PressSlash(Term*& t)
{
	throw (string)"No Action set for '/'";
	return 0;
}

int Input(Term*& t, char& key) // return 3 to exit InteractiveInput, -1 to exit program, 1 if input is not readable, 0 otherwise
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
			|| (KEYS_UPPER_CASE_LETTERS_START <= key && key <= KEYS_UPPER_CASE_LETTERS_END))
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
int Latex(Term*& t)
{
	// Write to file
	string compilePdfLatex =
	"\\documentclass{standalone}\n"
	"\\begin{document}\n"
		"\t$\\displaystyle\n\t"
		+ (string)t->Tex() +
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
int InteractiveInput(Term*& t)
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
				if (debugText.length() > CONSOLE_WIDTH)
					debugText = debugText.substr(debugText.length() - CONSOLE_WIDTH, CONSOLE_WIDTH); // Restrict length to prevent overflow
				cout << string(CONSOLE_WIDTH - debugText.length(), ' ') << debugText << endl;
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
void ShellLoop()
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

int main(int argc, char **argv)
{
	debugText = "";
	ShellLoop();
	cout << "Exit." << endl;
	return 0;
}
