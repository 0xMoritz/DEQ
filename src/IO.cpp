#include "IO.h"

using namespace std;


IO::IO()
{
	
}

void IO::InsertDigit(Term*& t, int digit)
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
void IO::Backspace(Term*& t)
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

void IO::Delete(Term*& t)
{
	throw (string)"Delete has not yet been implemented";
}


// Print Latex Equation
int IO::Latex(Term*& t)
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
