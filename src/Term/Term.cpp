#include "Term.h"

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
