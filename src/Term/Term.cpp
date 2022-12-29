#include "Term.h"
#include "../TermsAutonomous/Cursor.h"

using namespace std;

Term::Term(Term* _parent)
{
	parent = _parent;
}

Term::~Term()
{
	//cout << "killing base. ";
}

Term* Term::GetParent()
{
	return parent;
}

void Term::SetParent(Term* newParent)
{
	parent = newParent;
}

string Term::GetTex()
{
	if (dynamic_cast<Term*>(this) == Cursor::GetActive()->GetLeft())
		return "\\mathbin{\\color{red}" + Tex() + "}";
	else if (dynamic_cast<Term*>(this) == Cursor::GetActive()->GetRight())
		return "\\mathbin{\\color{green}" + Tex() + "}";
	else
		return Tex();
}

vector<Term*> Term::GetSubTerms()
{
	throw (string)"Called GetSubTerms on Term base object";
}

Term Term::Derivative()
{
	return (*this);
}

string Term::Print()
{
	return "err";
}

string Term::Tex()
{
	return "err";
}

int Term::Tree(StringTree& tree, int& maxDepth)
{
	maxDepth = 1;
	// return value is length of string
	tree.s = "(" + treeLabel + ")";
	return treeLabel.length() + 2;
}

Term* Term::WithoutCursor(Term* t)
{
	return t;//TODO
}

void Term::ReplaceSubTerm(Term* oldTerm, Term* newTerm)
{
	throw (string)"Function Replace has been called on Term" + PtrAddress(this) + "without subTerms";
}

string Term::PtrAddress(Term* ptr)
{
	const void * address = static_cast<const void*>(ptr);
	stringstream ss;
	ss << address;
	string addressString = ss.str();
	return addressString;
}

size_t Term::GetNumberOfSubTerms()
{
	throw (string)"GetNumberOfSubTerms called on Term base class";
}
