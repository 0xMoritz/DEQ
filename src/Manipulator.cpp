#include "Manipulator.h"

using namespace std;


Manipulator::Manipulator()
{
	root = new Cursor(rootParent);
	Cursor::SetActive(dynamic_cast<Cursor*>(root));
}

void Manipulator::Replace(Term* oldTerm, Term* newTerm)
{
	// For now we assume, that the old Term didn't have subTerms
	// assert(dynamic_cast<AutonomousTerm*>(oldTerm) != nullptr);
	assert(oldTerm != nullptr);
	assert(newTerm != nullptr);
	if (oldTerm == rootParent) // trying to insert beyond root -> shift root
	{
		root = newTerm;
		newTerm->SetParent(rootParent);
		debugText += "Replaced Root (beyond).";
	}
	else if (oldTerm->GetParent() == rootParent) // oldTerm == root
	{
		assert(oldTerm == root);
		root = newTerm;
		newTerm->SetParent(rootParent);
		debugText += "Replaced Root.";
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
		if (roof->GetParent() == rootParent)
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
		if (roof->GetParent() == rootParent)
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
	// Create the necessary object
	if (CursorLeft() == nullptr)
	{
		Connection* connect;
		if (0==Term::IsType<Connection>(c->GetParent()))
		{
			connect = new Connection(c->GetParent());
			Replace(c, connect);
			connect->AppendRight(c); // c will be the only subTerm anyway
		}
		else
			connect = dynamic_cast<Connection*>(c->GetParent());

		Raw* newRaw = new Raw(connect);
		connect->InsertSubTerm(c, newRaw, 0);
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

void Manipulator::InsertAddition(char sign)
{
	/*Cursor* c = Cursor::GetActive();
	Term* parentUp1 = c->GetParent();
	if (Term::IsType<Connect2>(parentUp1))
	{
		Term* parentUp2 = parentUp1->GetParent();
		if (Term::IsType<Connect2>(parentUp2))
		{
			// Construction is:
			//       co2(up2)             co2(up2)
			//       /    |               /      |
			//      ?  co2(up1)    or    ?    co2(up1)
			//        /       |              /      |
			//     cursor     ?              ?     cursor
			Term* right = CursorRight();
			Term* left = CursorLeft();
			if (Term::IsType<Raw>(left) && Term::IsType<Raw>(right))
			{
				Addition* add = new Addition(parentUp2->GetParent());
				Replace(parentUp2, add);
				add->AppendRight(left, ' ');
				Connect2* newCo2 = new Connect2(add);
				add->AppendRight(newCo2, sign);
				newCo2->SetSub1(c);
				c->SetParent(newCo2);
				newCo2->SetSub2(right);
				right->SetParent(newCo2);
				DeleteTerm(parentUp1);
				DeleteTerm(parentUp2);
			}
			else
				throw (string) "Undefined case while inserting Addition";
		}
		else
			throw (string) "Undefined case while inserting Addition";
	}
	else
		throw (string) "Undefined case while inserting Addition";*/
}

void Manipulator::CursorMoveLeft()
{
	Cursor* c = Cursor::GetActive();
	if (CursorLeft() == nullptr)
		return;
	if (Term::IsType<Connection>(c->GetParent()))
	{
		Connection* connect = dynamic_cast<Connection*>(c->GetParent());
		if (Term::IsType<Raw>(CursorLeft())) // Left already has a Raw type
		{
			Raw* left = dynamic_cast<Raw*>(CursorLeft());
			string swap = left->BackspaceContent();
			Term* right = CursorRight();
			// If there is no Raw Term to the right: create one
			if (!Term::IsType<Raw>(right))
			{
				right = new Raw(connect);
				connect->InsertSubTerm(c, right, +1); // Insert sets parent of right
			}
			dynamic_cast<Raw*>(right)->AppendLeft(swap);
			// Add swap to the right

			if (left->IsEmpty())
			{
				assert(left->GetParent() == connect);
				connect->RemoveSubTerm(left);
				DeleteTerm(left);
			}
		}
		else
			throw (string)"Not yet implemented";
	}
	else
		throw (string)"Not yet implemented";
}

void Manipulator::CursorMoveRight()
{
	// Analogous to CursorMoveLeft - so far
	Cursor* c = Cursor::GetActive();
	if (CursorRight() == nullptr)
		return;
	if (Term::IsType<Connection>(c->GetParent()))
	{
		Connection* connect = dynamic_cast<Connection*>(c->GetParent());
		if (Term::IsType<Raw>(CursorRight())) // Right already has a Raw type
		{
			Raw* right = dynamic_cast<Raw*>(CursorRight());
			string swap = right->DelContent();
			Term* left = CursorLeft();
			// If there is no Raw Term to the left: create one
			if (!Term::IsType<Raw>(left))
			{
				left = new Raw(connect);
				connect->InsertSubTerm(c, left, 0); // Insert sets parent of left
			}
			dynamic_cast<Raw*>(left)->AppendRight(swap);
			// Add swap to the right

			if (right->IsEmpty())
			{
				assert(right->GetParent() == connect);
				connect->RemoveSubTerm(right);
				DeleteTerm(right);
			}
		}
		else
			throw (string)"Not yet implemented";
	}
	else
		throw (string)"Not yet implemented";
}

void Manipulator::Backspace()
{
	if (CursorLeft() == nullptr)
		return;
	if (Term::IsType<Raw>(CursorLeft()))
	{
		Raw* raw = dynamic_cast<Raw*>(CursorLeft());
		raw->BackspaceContent();
		if (raw->IsEmpty())
			RemoveEmptyRaw(raw);
	}
}

void Manipulator::Del()
{
	if (CursorRight() == nullptr)
		return;
	if (Term::IsType<Raw>(CursorRight()))
	{
		Raw* raw = dynamic_cast<Raw*>(CursorRight());
		raw->DelContent();
		if (raw->IsEmpty())
			RemoveEmptyRaw(raw);
	}
}

void Manipulator::RemoveEmptyRaw(Raw* raw)
{
	assert(Term::IsType<Connection>(raw->GetParent()));
	Connection* parent = dynamic_cast<Connection*>(raw->GetParent());
	parent->RemoveSubTerm(raw);
	DeleteTerm(raw);
	if (parent->GetNumberOfSubTerms() <= 1) // Only remaining subTerm is Cursor
	{
		Term* c = Cursor::GetActive();
		assert(parent->GetSubTerms().front() == c);
		Replace(parent, c);
		DeleteTerm(parent);
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

bool Manipulator::CheckTermLinks(Term*& t)
{
	// Recursion
	if (t == nullptr)
	{
		return 1;
	}
	else if (t == root)
	{
		if (t->GetParent() != rootParent)
			return 1;
	}
	vector<Term*> subTerms = t->GetSubTerms();
	for (vector<Term*>::iterator it = subTerms.begin(); it != subTerms.end(); it++)
	{
		if (*it == nullptr)
			return 1;
		else if ((*it)->GetParent() != t)
			return 1;
		else if (CheckTermLinks(*it))
			return 1;
	}
	return 0;
}


void Manipulator::DeleteTerm(Term* t)
{
	// Delete all possible variables pointing to it
	// Pointer from old children
	assert(t != nullptr);
	vector<Term*> subTerms = t->GetSubTerms();
	for (vector<Term*>::iterator it = subTerms.begin(); it != subTerms.end(); it++)
	{
		if (*it != nullptr)
			if ((*it)->GetParent() == t)
				(*it)->SetParent(nullptr);
	}
	// Pointer from parent
	if (t->GetParent() != nullptr && t->GetParent() != rootParent)
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
