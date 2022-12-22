#include "DEQ.h"

const int KEY_ENTER = 10;
const int KEY_ESCAPE = 27;
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

using namespace std;

// Static variable Initilization
string FilePrinter::outputPath{"latex/"};

int PressUpArrow(Term* t)
{
	cout << "PressUpArrow" << endl;
	return 0;
}
int PressDownArrow(Term* t)
{
	cout << "PressDownArrow" << endl;
	return 0;
}
int PressRightArrow(Term* t)
{
	cout << "PressRightArrow" << endl;
	return 0;
}
int PressLeftArrow(Term* t)
{
	cout << "PressLeftArrow" << endl;
	return 0;
}
int PressEscape(Term* t)
{
	cout << "PressEscape" << endl;
	return 0;
}
int PressNumber(Term* t, int num)
{
	cout << "PressNumber " << num << endl;
	return 0;
}
int PressLetter(Term* t, char ch)
{
	cout << "PressLetter " << ch << endl;
	return 0;
}
int PressEnter(Term* t)
{
	cout << "PressEnter" << endl;
	return 0;
}
Enter
int Input(Term* t) // return 3 to exit InteractiveInput, -1 to exit program, 1 if input is not readable, 0 otherwise
{
	char key;
	if (read(STDIN_FILENO, &key, 1) != 1)
	{
		cerr << stderr << " read error or EOF\n";
		return 1;
	}
	if (key == KEY_EOF)
	{
		cerr << stderr << " " << key << " (control-D or EOF)\n";
		return -1;
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
					cerr << "[Error] Noticed Escape sequence but could not decipher " << key << endl;
					return 1;
				}
			}
			else
			{
				cerr << "[Error] Noticed Escape sequence but could not decipher " << key << endl;
				return 1;
			}
		}
		else if (selret == -1)
		{
			cerr << "[Error] " << errno << endl;
			return 1;
		}
		else
		{
			PressEscape(t);
			return 3;
		}
	}
	else  // no escape sequence
	{
		if (key == KEY_ENTER)
		{
			return PressEnter(t);
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
		cerr << "[Error] Illegal input: " << (int)key << endl;
	}
	return key;
}

void PrintTermToConsole(Term* t)
{
	cout << t->Print() << endl;
}

int PrintTreeToConsole(Term* t) // return maxDepth
{
	StringTree tree{};
	int maxDepth = 0;
	t->Tree(tree, maxDepth);
	cout << tree.Write(maxDepth) << endl;
	return maxDepth;
}


// Print Latex Equation
int Latex(Term* t)
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
int InteractiveInput(Term* t)
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
	while (1)
	{
		int in = Input(t);
		if (in == 3)
		{
			res = 0;
			break;
		}
		else if (in == -1)
		{
			res = -1;
			break;
		}
		// Overwrite last tree
		for (int i = 0; i < depth+3; i++)
		{
			cout << "\033[A" << "\33[2K"; // Delete and move up
		}
		cout << "\b"; // Bring back cursor
		PrintTermToConsole(t);
		depth = PrintTreeToConsole(t);
	}

	// set terminal back to canonical
	tcsetattr(fd, TCSANOW, &oldTermios);
	return res;
}

// Standard Loop for manipulation
void ShellLoop()
{
	Term* t = new Addition(new list<Term*>{new Power(new Number("1"), new Multiplication(new list<Term*>{new Number("9"), new Number("8")})), new Number("2"), new Number("3"), new Connect2{new Text("Hallo"), new Power(new Variable("\\psi_{4x}"), new Text("Welt"))}});

	while (1)
	{
		string in;
		cout << "> ";
		cin >> in;
		if (in == "i" || in == "Interactive")
		{
			cout << "Entering Interactive input" << endl << endl;
			int out = InteractiveInput(t);
			if (out == -1)
			break;
			cout << endl << "Interactive Input exited with " << out << endl;
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
	ShellLoop();
	cout << "Exit." << endl;
	return 0;
}


/*
void pause(int t) {
	std::this_thread::sleep_for(std::chrono::milliseconds(t));
}

static const int width = 40;

void show_percent(int i) {
	 int dashes = (width * i)/100;

	 std::cout << '|' << std::left << std::setw(width) << std::string(dashes, '-') << '|' << std::setw(3) << i << "%";
}


// percent bar
int main() {

	for (int i=0; i<101; i++) {
		show_percent(i);
		std::cout << std::string(width+6, '\b');
		pause(100);
	}
}*/
