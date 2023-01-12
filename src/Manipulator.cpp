#include "Manipulator.h"

using namespace std;


Manipulator::Manipulator()
{
	rootTerm = new Cursor(rootTermParent);
	Cursor::SetActive(dynamic_cast<Cursor*>(rootTerm));
}

void Manipulator::Replace(Term* oldTerm, Term* newTerm)
{
	// For now we assume, that the old Term didn't have subTerms
	// assert(dynamic_cast<AutonomousTerm*>(oldTerm) != nullptr);
	assert(oldTerm != nullptr);
	assert(newTerm != nullptr);
	Term* parent = oldTerm->GetParent();
	if (parent == nullptr)
	{
		throw (string)"parent == nullptr";
	}
	else if (oldTerm == rootTermParent) // trying to insert beyond rootTerm -> shift rootTerm
	{
		rootTerm = newTerm;
		newTerm->SetParent(rootTermParent);
		debugText += "Replaced rootTerm (beyond).";
	}
	else if (parent == rootTermParent) // oldTerm == rootTerm
	{
		assert(oldTerm == rootTerm);
		rootTerm = newTerm;
		newTerm->SetParent(rootTermParent);
		debugText += "Replaced rootTerm.";
	}
	else
	{
		// Replace
		parent->ReplaceSubTerm(oldTerm, newTerm);
	}
	oldTerm->SetParent(nullptr);
}

void Manipulator::SetrootTerm(Term*& _rootTerm)
{
	rootTerm = _rootTerm;
}
Term*& Manipulator::GetrootTerm()
{
	return rootTerm;
}

Term* Manipulator::CursorLeft()
{
	Cursor* c = Cursor::GetActive();
	// Determine roof
	Term* roof = c;
	Term* oldRoof = roof;
	while (1) // find the "roof" of the cursor, the first term in the line of parents, that has more than one child (which eventually leads to the cursor)
	{
		if (roof->GetParent() == rootTermParent)
		{
			assert(dynamic_cast<Term*>(roof) == rootTerm);
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
		if (roof->GetParent() == rootTermParent)
		{
			assert(dynamic_cast<Term*>(roof) == rootTerm);
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
	Cursor* c = Cursor::GetActive();
	//Term* parent = c->GetParent();
	Addition* add = new Addition(nullptr);
		//Replace(connect, add);
		// Take out Term before and after cursor and fill them into a new addition, that replaces the two Terms in the parent.
	Term* left = nullptr; // Term left to the new Plus
	Term* right = nullptr;
	SplitUntilAddition(c, left, right, add);
	add->AppendRight(left, ' ');
	add->AppendRight(right, '+');

	assert (c != rootTerm);
	Replace(c->GetParent(), add);
	//RecursiveCleanUp(rootTerm);
}

void Manipulator::CursorMoveLeft()
{
	Cursor* c = Cursor::GetActive();
	if (GetLeftmostTerm(rootTerm) == c)
		return;
	else if (Term::IsType<Connection>(c->GetParent()))
	{
		Connection* connect = dynamic_cast<Connection*>(c->GetParent());

		if (GetLeftmostTerm(connect) == c)
		{
			DebugLog("Under Construction");
			Term* left = CursorLeft();
			connect->RemoveSubTerm(c);
			Connection* newConnection = new Connection(left->GetParent());
			Replace(left, newConnection);
			newConnection->AppendRight(left);
			newConnection->AppendRight(c);
			RecursiveCleanUp(rootTerm);
		}
		else if (Term::IsType<Raw>(CursorLeft())) // Left already has a Raw type
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
	if (GetRightmostTerm(rootTerm) == c)
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

bool Manipulator::CheckTermLinks(Term*& t, vector<Term*>& errorTerms)
{
	bool areThereErrors = 0;
	// Recursion
	if (t == nullptr)
	{ errorTerms.push_back(t); areThereErrors = 1; }
	else if (t == rootTerm)
	{
		if (t->GetParent() != rootTermParent)
		{ errorTerms.push_back(t); areThereErrors = 1; }
	}
	vector<Term*> subTerms = t->GetSubTerms();
	for (vector<Term*>::iterator it = subTerms.begin(); it != subTerms.end(); it++)
	{
		if (*it == nullptr)
		{ errorTerms.push_back(*it); areThereErrors = 1; }
		else if ((*it)->GetParent() != t)
		{ errorTerms.push_back(*it); areThereErrors = 1; }
		else if (CheckTermLinks(*it, errorTerms))
		{ areThereErrors = 1; }
	}
	return areThereErrors;
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
	if (t->GetParent() != nullptr && t->GetParent() != rootTermParent)
		t->GetParent()->RemoveSubTerm(t);

	// Pointer from rootTerm
	if (rootTerm == t)
		rootTerm = nullptr;
}

void Manipulator::DeleteSubTerms(Term* t)
{
	// Delete whole subTree, could be dangerous
	//error
}


void Manipulator::SplitUntilMultiplication(Term* at, Term*& left, Term*& right)
{/*
	// Get the subTerms, find the iterator position of the cut and create lists to hold all the Terms before and all the Terms after the cut
	assert(Term::IsType<Connection>(at->GetParent()));
	Connection* connect = dynamic_cast<Connection*>(at->GetParent());
	vector<Term*> subTerms = connect->GetSubTerms();
	assert(subTerms.size() > 2);
	vector<Term*>::iterator it = subTerms.begin();
	vector<Term*> leftTerms;
	vector<Term*> rightTerms;
	vector<Term*>::iterator cutPos = connect->Find(at);
	// Go from the start to the cutPos and add all subTerms to the leftTerms list, then return a connection with that List or the Term itself if it's only one. For non return nullptr
	for (; it != cutPos; it++)
	{
		leftTerms.push_back(*it);
	}
	left = new Connection(newParent, leftTerms);
	// Do the same for the right part, after the cutPos
	for (it = cutPos; it != subTerms.end())
	{
		rightTerms.push_back(*t);
	}
	right = new Connection(newParent, rightTerms);
	// Delete the old Connection
	DeleteTerm(connect);*/
}

template<typename T>
void Manipulator::SplitMultiTerm(T* multi, Term* at, MultiTerm*& left, MultiTerm*& right)
{
	// Get the subTerms, find the iterator position of the cut and create lists to hold all the Terms before and all the Terms after the cut
	assert(at->GetParent() == multi);
	assert(Term::IsType<T>(at->GetParent()));
	vector<Term*> subTerms = multi->GetSubTerms();
	vector<char> symbols = multi->GetSymbols();
	assert(subTerms.size() > 2);
	vector<Term*>::iterator termIt = subTerms.begin();
	vector<char>::iterator symbolIt = symbols.begin();
	vector<Term*> leftTerms;
	vector<char> leftSymbols;
	vector<Term*> rightTerms;
	vector<char> rightSymbols;
	// Go from the start to the cutPos and add all subTerms to the leftTerms list, then return a multiion with that List or the Term itself if it's only one. For non return nullptr
	// reduce reduces left and right to hold only one Term or empty
	for (; *termIt != at; termIt++, symbolIt++)
	{
		leftTerms.push_back(*termIt);
		leftSymbols.push_back(*symbolIt);
	}
	left = new T(multi->GetParent(), leftTerms, leftSymbols);
	// Do the same for the right part, after the cutPos
	for (; termIt != subTerms.end(); termIt++, symbolIt++)
	{
		rightTerms.push_back(*termIt);
		rightSymbols.push_back(*symbolIt);
	}
	right = new T(multi->GetParent(), rightTerms, rightSymbols);
	// Delete the old multiion
	//DeleteTerm(multi);
}
template void Manipulator::SplitMultiTerm<Addition>(Addition* multi, Term* at, MultiTerm*& left, MultiTerm*& right);
template void Manipulator::SplitMultiTerm<Connection>(Connection* multi, Term* at, MultiTerm*& left, MultiTerm*& right);
template void Manipulator::SplitMultiTerm<Multiplication>(Multiplication* multi, Term* at, MultiTerm*& left, MultiTerm*& right);

void Manipulator::SplitUntilAddition(Term* at, Term*& left, Term*& right, MultiTerm* newParent)
{
	Term* cut = at;
	while (0==Term::IsType<Addition>(cut) && cut != rootTerm) // Is not addition TODO or brackets
	{
		Term* parent = cut->GetParent();
		while (0==Term::IsDerivedFrom<MultiTerm>(parent) && cut != rootTerm)
		{
			// This must be wrong, should maybe cut be appended on the line of newRight or smthing?
			DeleteTerm(cut);
			cut = parent;
			parent = cut->GetParent();
		}
		MultiTerm* newLeft = nullptr;
		MultiTerm* newRight = nullptr;
		if (Term::IsType<Addition>(parent))
			SplitMultiTerm<Addition>(dynamic_cast<Addition*>(parent), cut, newLeft, newRight);
		else if (Term::IsType<Multiplication>(parent))
			SplitMultiTerm<Multiplication>(dynamic_cast<Multiplication*>(parent), cut, newLeft, newRight);
		else if (Term::IsType<Connection>(parent))
			SplitMultiTerm<Connection>(dynamic_cast<Connection*>(parent), cut, newLeft, newRight);
		else
			throw (string)"SplitUntilAddition Error: Unkown MultiTerm";

		if (left != nullptr)
			newLeft->AppendRight(left);
		if (right != nullptr)
			newRight->AppendLeft(right);

		right = newRight;
		left = newLeft; // TODO vielleicht muss ich das rekursiv machen, weil ich sonst immer at lösche?


		if (cut != at)
			DeleteTerm(cut);
		cut = parent;
	}
}

void Manipulator::RecursiveCleanUp(Term* t)
{
	// Apply the RecursiveCleanUp from the branches first
	DebugLog(Term::PtrAddress(t));
	if (t->GetNumberOfSubTerms() == 0)
		return;
	for (vector<Term*>::iterator it = t->GetSubTerms().begin(); it != t->GetSubTerms().end(); it++)
	{
		Term* subTerm = *it;
		RecursiveCleanUp(subTerm);
		// Now incorporate subTerms if they are of the same MultiTerm Type
		if (Term::IsDerivedFrom<MultiTerm>(t)
		&& Term::IsDerivedFrom<MultiTerm>(subTerm)
		&& Term::AreTypesEqual(t, subTerm))
		// The new Term's subTerms can be added into the list of subTerms here, because of associative property
		{
			vector<Term*> newSubTerms = subTerm->GetSubTerms();
			vector<char> newSymbolList = dynamic_cast<MultiTerm*>(subTerm)->GetSymbols();

			vector<char>::iterator newSymbol = newSymbolList.begin();
			vector<Term*>::iterator newSubTerm = newSubTerms.begin();
			// For the first term there might be the case that the old subTerm has a minus in front
			if (Term::IsType<Addition>(t))
			{
				vector<char>::iterator oldTermSymbol;
				vector<Term*>::iterator tIt;
				dynamic_cast<MultiTerm*>(t)->FindWithSymbol(subTerm, tIt, oldTermSymbol);
				char combinedSymbol = ((*oldTermSymbol == '-' && *newSymbol == '-') || (*oldTermSymbol == '+' && *newSymbol == '+'))? '+' : '-';
				dynamic_cast<MultiTerm*>(t)->InsertSubTerm(subTerm, *newSubTerm, combinedSymbol, 0);
				newSymbol++;
				newSubTerm++;
			}

			for (; newSubTerm != newSubTerms.end(); newSubTerm++, newSymbol++)
			{
				dynamic_cast<MultiTerm*>(t)->InsertSubTerm(subTerm, *newSubTerm, *newSymbol, 0);
			}
			dynamic_cast<MultiTerm*>(t)->RemoveSubTerm(subTerm);
			subTerm->SetParent(nullptr);
			DeleteTerm(subTerm);
		}
	}
	// Reduce this term if it has no subTerms
	ReduceTerm(t);
}

void Manipulator::ReduceTerm(Term* t)
{
	if (Term::IsDerivedFrom<MultiTerm>(t))
	{
		vector<Term*> subTerms = t->GetSubTerms();
		// Replace the multiTerm Empty if there are no subTerms
		if (subTerms.size() == 0)
		{
			Replace(t, new Empty(t->GetParent()));
			DeleteTerm(t);
		}
		// Replace the multiTerm with its only subTerm
		else if (subTerms.size() == 1)
		{
			Replace(t, subTerms.front());
			DeleteTerm(t);
		}
	}
	// No Reduction mechanisms for other Term types so far
}
/*
{
	// Get the subTerms, find the iterator position of the cut and create lists to hold all the Terms before and all the Terms after the cut
	vector<Term*> subTerms = connect->GetSubTerms();
	assert(subTerms.size() > 2);
	vector<Term*>::iterator it = subTerms.begin();
	vector<Term*> leftTerms;
	vector<Term*> rightTerms;
	vector<Term*>::iterator cutPos = connect->Find(at);
	// Go from the start to the cutPos and add all subTerms to the leftTerms list, then return a connection with that List or the Term itself if it's only one. For non return nullptr
	for (; it != cutPos; it++)
	{
		leftTerms.push_back(*it);
	}
	if (leftTerms.size() == 0)
		left = new Empty(newParent);
	else if (leftTerms.size() == 1)
	 	left = leftTerms[0];
	else
		left = new Connection(newParent, leftTerms);
	// Do the same for the right part, after the cutPos
	for (it = cutPos; it != subTerms.end())
	{
		rightTerms.push_back(*t);
	}
	if (rightTerms.size() == 0)
		right = new Empty(newParent);
	else if (rightTerms.size() == 1)
		right = rightTerms[0];
	else
		right = new Connection(newParent, rightTerms);
	// Delete the old Connection
	DeleteTerm(connect);
} */
