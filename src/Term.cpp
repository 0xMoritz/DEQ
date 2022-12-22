#include "Term.h"

using namespace std;


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


// class SingularTerm


// BinaryTerm
BinaryTerm::BinaryTerm(Term* _sub1, Term* _sub2)
{
	sub1 = _sub1;
	sub2 = _sub2;
}
int BinaryTerm::Tree(StringTree& tree, int& maxDepth)
{
	int len = 0;
	maxDepth = 0;
	int subMaxDepth = 0;
	StringTree* subTree;

	subTree = new StringTree{};
	tree.subTrees.push_back(subTree);
	len += sub1->Tree(*subTree, subMaxDepth);
	maxDepth = max(maxDepth, subMaxDepth);

	subTree = new StringTree{};
	tree.subTrees.push_back(subTree);
	len += sub2->Tree(*subTree, subMaxDepth);
	maxDepth = max(maxDepth, subMaxDepth);

	// Display label in the middle
	int totalPadding = len - 2 - this->treeLabel.length();
	int leftPadding = totalPadding / 2;
	tree.s = "(" + string(leftPadding, ' ') + this->treeLabel + string(totalPadding - leftPadding, ' ') + ")";

	maxDepth++; // Count this term itself
	return len;
}


// class MultiTerm
int MultiTerm::Tree(StringTree& tree, int& maxDepth)
{
	if (subTerms->size() > 0)
	{
		int len = 0;
		maxDepth = 0;
		for (auto subTerm = subTerms->begin(); subTerm != subTerms->end(); subTerm++)
		{
			int subMaxDepth = 0;
			StringTree* subTree = new StringTree{};
			tree.subTrees.push_back(subTree);
			len += (**subTerm).Tree(*subTree, subMaxDepth);
			maxDepth = max(maxDepth, subMaxDepth);
		}
		// Display label in the middle
		int totalPadding = len - 2 - this->treeLabel.length();
		int leftPadding = totalPadding / 2;
		tree.s = "(" + string(leftPadding, ' ') + this->treeLabel + string(totalPadding - leftPadding, ' ') + ")";

		maxDepth++; // Count this term itself
		return len;
	}
	return Term::Tree(tree, maxDepth);
}
