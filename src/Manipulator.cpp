#include "Manipulator.h"

using namespace std;


Manipulator::Manipulator()
{
	root = new Cursor(nullptr);
	Cursor::SetActive(dynamic_cast<Cursor*>(root));
}

void Manipulator::Replace(Term* oldTerm, Term* newTerm)
{
	// For now we assume, that the old Term didn't have subTerms
	// assert(dynamic_cast<AutonomousTerm*>(oldTerm) != nullptr);
	assert(oldTerm != nullptr);
	assert(newTerm != nullptr);
	if (oldTerm->GetParent() == nullptr) // == root
	{
		assert(oldTerm == root);
		root = newTerm;
		newTerm->SetParent(nullptr);
		//debugText += "replaced Root with cursor";
	}
	else
	{
		oldTerm->GetParent()->ReplaceSubTerm(oldTerm, newTerm);
	}
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
	if (Term::IsType<Raw>(c->GetLeft()))
	{
		dynamic_cast<Raw*>(c->GetLeft())->AppendRight(to_string(digit));
	}
	else
	{
		throw (string)"Could not add digit";
	}

}

void Manipulator::CursorMoveLeft()
{
	Cursor* c = Cursor::GetActive();
	if (c->GetLeft() == nullptr)
		return;
	if (Term::IsType<Raw>(c->GetLeft()))
	{
		Raw* raw = dynamic_cast<Raw*>(c->GetLeft());
		string swap = raw->Backspace();
		// if raw becomes "empty"
		if (raw->IsEmpty())
		{
			assert(Term::IsType<Connect2>(c->GetParent()));
			///TODO, attention with the hirarchy...
		}
	}
}

void Manipulator::CursorMoveRight()
{
	Cursor* c = Cursor::GetActive();
	if (c->GetRight() == nullptr)
		return;
	if (Term::IsType<Raw>(c->GetRight()))
	{/*
		TODO: first finish move left
		Raw* raw = dynamic_cast<Raw*>(c->GetLeft());
		string swap = raw->Backspace();
		// if raw becomes "empty"
		if (raw->IsEmpty())
		{
			//TODO: implement a replace method.
			///TODO, attention with the hirarchy...
		}*/
	}
}

void Manipulator::FindCursorNeighbours()
{
	Cursor* c = Cursor::GetActive();

	// Find left Neighbour
	Term* roof = c;

	// Determine roof
	while (1) // find the "roof" of the cursor, the first term in the line of parents, that has more than one child (which eventually leads to the cursor)
	{
		if (roof->GetParent() == nullptr)
		{
			assert(dynamic_cast<Term*>(roof) == root);
			c->SetLeft(nullptr);
			return;
		}
		roof = roof->GetParent();
		if (roof->GetNumberOfSubTerms() > 1)
		{
			// Check if the additional Terms of that parent are left of the cursor
			vector<Term*> roofSubs = roof->GetSubTerms();
			vector<Term*>::iterator it = begin(roofSubs);
			for (;it != end(roofSubs); it++)
			{
				if (*it == roof)
					break;
			}
			 //vector<Term*>::iterator
			if (*it != roofSubs.front())
			{
				c->SetLeft(GetRightmostTerm(*(--it)));
				return;
			}
		}
		else
		{
			assert(roof->GetNumberOfSubTerms() != 0);
			// Step up one layer to find roof
			roof = roof->GetParent();
		}
	}

	roof = c;

	// Determine roof
	while (1) // find the "roof" of the cursor, the first term in the line of parents, that has more than one child (which eventually leads to the cursor)
	{
		if (roof->GetParent() == nullptr)
		{
			assert(dynamic_cast<Term*>(roof) == root);
			c->SetRight(nullptr);
			break;
		}
		roof = roof->GetParent();
		if (roof->GetNumberOfSubTerms() > 1)
		{
			// Check if the additional Terms of that parent are right of the cursor
			vector<Term*> roofSubs = roof->GetSubTerms();
			vector<Term*>::iterator it = begin(roofSubs);
			for (;it != end(roofSubs); it++)
			{
				if (*it == roof)
					break;
			}
			 //vector<Term*>::iterator
			if (*it != roofSubs.front())
			{
				c->SetRight(GetLeftmostTerm(*(++it)));
				break;
			}
		}
		else
		{
			assert(roof->GetNumberOfSubTerms() != 0);
			// Step up one layer to find roof
			roof = roof->GetParent();
		}
	}
}

Term* Manipulator::GetRightmostTerm(Term* t)
{
	while(t->GetNumberOfSubTerms() > 0)
	{
		t = t->GetSubTerms().back();
	}
	return t;
}

Term* Manipulator::GetLeftmostTerm(Term* t)
{
	while(t->GetNumberOfSubTerms() > 0)
	{
		t = t->GetSubTerms().front();
	}
	return t;
}

void Manipulator::Backspace()
{
	Cursor* c = Cursor::GetActive();
	if (c->GetLeft() == nullptr)
		return;
	if (Term::IsType<Raw>(c->GetLeft()))
	{
		Raw* raw = dynamic_cast<Raw*>(c->GetLeft());
		raw->Backspace();
		// if raw becomes "empty"
		if (raw->IsEmpty())
		{
			Term* parent = c->GetParent();
			assert(Term::IsType<Connect2>(parent));
			Replace(parent, dynamic_cast<Term*>(c));
			delete parent;
			delete raw;
			//TODO
			FindCursorNeighbours();
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
	string eq = t->GetTex();
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
	"\\usepackage{xcolor}\n"
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
