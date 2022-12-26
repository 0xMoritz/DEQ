#include "Manipulator.h"

using namespace std;


Manipulator::Manipulator()
{
	root = new Cursor(nullptr);
	Cursor::SetActive(dynamic_cast<Cursor*>(root));
}

void Manipulator::SetRoot(Term*& _root)
{
	root = _root;
}
Term*& Manipulator::GetRoot()
{
	return root;
}

void Manipulator::InsertDigit(int digit)
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
			assert(root==c);
			root = static_cast<Term*>(newParent);
		}
		Raw* newRaw = new Raw(newParent);
		newParent->SetSub1(newRaw);
		c->SetParent(newParent);
		c->SetLeft(newRaw);
		newParent->SetSub2(c);
	}
	// Add the actual digit
	if (typeid(*c->GetLeft()) == typeid(Raw))
	{
		dynamic_cast<Raw*>(c->GetLeft())->Append(to_string(digit));
	}
	else
	{
		throw (string)"Could not add digit";
	}

}
void Manipulator::Backspace()
{
	Cursor* c = Cursor::GetActive();
	if (c->GetLeft() == nullptr)
		return;
	if (typeid(*c->GetLeft()) == typeid(Raw))
	{
		Raw* raw = dynamic_cast<Raw*>(c->GetLeft());
		raw->Backspace();
		// if raw becomes "empty"
		if (raw->IsEmpty())
		{
			//TODO: implement a replace method.
			assert(typeid(*c->GetParent()) == typeid(Connect2));
			///TODO, attention with the hirarchy...
		}
	}
}
void Manipulator::CursorMoveLeft()
{
	Cursor* c = Cursor::GetActive();
	if (c->GetLeft() == nullptr)
		return;
	if (typeid(*c->GetLeft()) == typeid(Raw))
	{
		Raw* raw = dynamic_cast<Raw*>(c->GetLeft());
		raw->Backspace();
		// if raw becomes "empty"
		if (raw->IsEmpty())
		{
			//TODO: implement a replace method.
			assert(typeid(*c->GetParent()) == typeid(Connect2));
			///TODO, attention with the hirarchy...
		}
	}
}
void Manipulator::CursorMoveRight()
{
	Cursor* c = Cursor::GetActive();
	if (c->GetLeft() == nullptr)
		return;
	if (typeid(*c->GetLeft()) == typeid(Raw))
	{
		Raw* raw = dynamic_cast<Raw*>(c->GetLeft());
		raw->Backspace();
		// if raw becomes "empty"
		if (raw->IsEmpty())
		{
			//TODO: implement a replace method.
			assert(typeid(*c->GetParent()) == typeid(Connect2));
			///TODO, attention with the hirarchy...
		}
	}
}

void Manipulator::Delete()
{
	throw (string)"Delete has not yet been implemented";
}


// Print Latex Equation
int Manipulator::Latex(Term*& t)
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
