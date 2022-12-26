#include "Term.h"

using namespace std;

Term::Term(Term* _parent)
{
	parent = _parent;
}
Term* Term::GetParent()
{
	return parent;
}
void Term::SetParent(Term* newParent)
{
	parent = newParent;
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
