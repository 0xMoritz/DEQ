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

Term* Manipulator::CursorLeft()
{
	Cursor* c = Cursor::GetActive();
	// Determine roof
	Term* roof = c;
	Term* oldRoof = roof;
	while (1) // find the "roof" of the cursor, the first term in the line of parents, that has more than one child (which eventually leads to the cursor)
	{
		if (roof->GetParent() == nullptr)
		{
			assert(dynamic_cast<Term*>(roof) == root);
			return nullptr;
		}
		oldRoof = roof;
		roof = roof->GetParent();
		if (roof->GetNumberOfSubTerms() > 1)
		{
			// Check if the additional Terms of that parent are left of the cursor
			vector<Term*> roofSubs = roof->GetSubTerms();
			for (vector<Term*>::iterator it=++roofSubs.begin();it != roofSubs.end(); it++)
			{
				if (*it == oldRoof)
					return GetRightmostTerm(*(--it));
			}
		}
	}
	throw (string)"Could not find Cursorleft()";
}

Term* Manipulator::CursorRight()
{
	Cursor* c = Cursor::GetActive();
	// Determine roof
	Term* roof = c;
	Term* oldRoof = roof;
	while (1) // find the "roof" of the cursor, the first term in the line of parents, that has more than one child (which eventually leads to the cursor)
	{
		if (roof->GetParent() == nullptr)
		{
			assert(dynamic_cast<Term*>(roof) == root);
			return nullptr;
		}
		oldRoof = roof;
		roof = roof->GetParent();
		if (roof->GetNumberOfSubTerms() > 1)
		{
			// Check if the additional Terms of that parent are right of the cursor
			vector<Term*> roofSubs = roof->GetSubTerms();
			for (vector<Term*>::iterator it=roofSubs.begin();it != --roofSubs.end(); it++)
			{
				if (*it == oldRoof)
					return GetLeftmostTerm(*(++it));
			}
		}
	}
	throw (string)"Could not find CursorRight()";
}

Term* Manipulator::GetRightmostTerm(Term* t)
{
	if (t==nullptr)
		return nullptr;
	while(t->GetNumberOfSubTerms() > 0)
	{
		//DebugLog(to_string(t->GetNumberOfSubTerms()));
		t = t->GetSubTerms().back();
		//DebugLog("t==nullptr:" + (t == nullptr)? "1" : "0");
		//DebugLog(typeid(t).name());
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

void Manipulator::InsertDigit(int digit)
{
	Cursor* c = Cursor::GetActive();
	assert(c != nullptr);
	// Create the necessary object
	if (CursorLeft() == nullptr)
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
		newParent->SetSub2(c);
	}
	// Add the actual digit
	if (Term::IsType<Raw>(CursorLeft()))
	{
		dynamic_cast<Raw*>(CursorLeft())->AppendRight(to_string(digit));
	}
	else
	{
		throw (string)"Could not add digit";
	}

}

void Manipulator::CursorMoveLeft()
{
	Cursor* c = Cursor::GetActive();
	if (CursorLeft() == nullptr)
		return;
	if (Term::IsType<Raw>(CursorLeft()))
	{
		Raw* left = dynamic_cast<Raw*>(CursorLeft());
		string swap = left->Backspace();
		// Add swap to the right
		if (Term::IsType<Raw>(CursorRight()))
		{
			Raw* right = dynamic_cast<Raw*>(CursorRight());
			right->AppendLeft(swap);
		}
		else
		{
			// Construct a suspension such that
			//             co2
			//            /   |
			//			co2  right
			//         /   |
			//      left  cursor
			assert(Term::IsType<Connect2>(c->GetParent()));
			Connect2* leftCo2 = dynamic_cast<Connect2*>(c->GetParent());
			Connect2* rightCo2 = new Connect2(leftCo2->GetParent());
			Replace(leftCo2, rightCo2);
			rightCo2->SetSub1(leftCo2);

			Raw* right = new Raw(rightCo2);
			rightCo2->SetSub2(right);
			right->AppendLeft(swap);
		}

		if (left->IsEmpty())
		{
			Term* parent = c->GetParent();
			assert(Term::IsType<Connect2>(parent));
			Replace(parent, dynamic_cast<Term*>(c));
			DeleteTerm(parent);
			DeleteTerm(left);
		}
	}
}

void Manipulator::CursorMoveRight()
{
	Cursor* c = Cursor::GetActive();
	if (CursorRight() == nullptr)
		return;
	if (Term::IsType<Raw>(CursorRight()))
	{/*
		TODO: first finish move left
		Raw* raw = dynamic_cast<Raw*>(CursorLeft());
		string swap = raw->Backspace();
		// if raw becomes "empty"
		if (raw->IsEmpty())
		{
			//TODO: implement a replace method.
			///TODO, attention with the hirarchy...
		}*/
	}
}

void Manipulator::Backspace()
{
	if (CursorLeft() == nullptr)
		return;
	if (Term::IsType<Raw>(CursorLeft()))
	{
		Raw* raw = dynamic_cast<Raw*>(CursorLeft());
		raw->Backspace();
		// if raw becomes "empty"
		if (raw->IsEmpty())
		{
			assert(Term::IsType<Connect2>(raw->GetParent()));
			Connect2* parent = dynamic_cast<Connect2*>(raw->GetParent());
			Replace(parent, parent->GetSub2());
			DeleteTerm(parent);
			DeleteTerm(raw);
		}
	}
}

void Manipulator::Delete()
{
	if (CursorRight() == nullptr)
		return;
	if (Term::IsType<Raw>(CursorRight()))
	{
		Raw* raw = dynamic_cast<Raw*>(CursorRight());
		raw->Delete();
		// if raw becomes "empty"
		if (raw->IsEmpty())
		{
			assert(Term::IsType<Connect2>(raw->GetParent()));
			Connect2* parent = dynamic_cast<Connect2*>(raw->GetParent());
			Replace(parent, parent->GetSub1());
			DeleteTerm(parent);
			DeleteTerm(raw);
		}
	}
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

bool Manipulator::CheckConnections(Term*& t)
{
	//error
}


void Manipulator::DeleteTerm(Term* t)
{
	// Delete all possible variables pointing to it
	// Pointer from old children
	vector<Term*> subTerms = t->GetSubTerms();
	for (vector<Term*>::iterator it = subTerms.begin(); it != subTerms.end(); it++)
	{
		if ((*it)->GetParent() == t)
			(*it)->SetParent(nullptr);
	}
	// Pointer from parent
	if (t->GetParent() != nullptr)
		t->GetParent()->ReplaceSubTerm(t, nullptr);
	// Pointer from root
	if (root == t)
		root = nullptr;
}

void Manipulator::DeleteSubTerms(Term* t)
{
	// Delete whole subTree, could be dangerous
	//error
}
