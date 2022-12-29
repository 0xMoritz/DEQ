#include "BinaryTerm.h"

using namespace std;

// BinaryTerm
BinaryTerm::BinaryTerm(Term* _parent) : Term(_parent)
{

}

BinaryTerm::BinaryTerm(Term* _parent, Term* _sub1, Term* _sub2) : Term(_parent)
{
	sub1 = _sub1;
	sub2 = _sub2;
}

BinaryTerm::~BinaryTerm()
{
	//cout << "Killing BinaryTerm. " << endl;
}

list<Term*> BinaryTerm::GetSubTerms()
{
	return list<Term*>{sub1, sub2};
}

Term* BinaryTerm::GetSub1()
{
	return sub1;
}

void BinaryTerm::SetSub1(Term* newSub1)
{
	sub1 = newSub1;
}

Term* BinaryTerm::GetSub2()
{
	return sub2;
}

void BinaryTerm::SetSub2(Term* newSub2)
{
	sub2 = newSub2;
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

void BinaryTerm::ReplaceSubTerm(Term* oldTerm, Term* newTerm)
{
	oldTerm->SetParent(nullptr);
	newTerm->SetParent(this);

	if (sub1 == oldTerm)
	{
		sub1 = newTerm;
	}
	else if (sub2 == oldTerm)
	{
		sub2 = newTerm;
	}
	else
	{
		throw (string)"Replace method was called in BinaryTerm " + PtrAddress(this) + " but Term to replace couldn't be found";
	}
}
