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

vector<Term*> BinaryTerm::GetSubTerms()
{
	return vector<Term*>{sub1, sub2};
}

Term* BinaryTerm::GetSub1()
{
	return sub1;
}

void BinaryTerm::SetSub1(Term* newSub1)
{
	sub1 = newSub1;
	if (sub1 != nullptr)
	{
		sub1->SetParent(this);
	}
}

Term* BinaryTerm::GetSub2()
{
	return sub2;
}

void BinaryTerm::SetSub2(Term* newSub2)
{
	sub2 = newSub2;
	if (sub2 != nullptr)
	{
		sub2->SetParent(this);
	}
}

int BinaryTerm::Tree(StringTree& tree, int& maxDepth, bool withPtr)
{
	int len = 0;
	maxDepth = 0;
	int subMaxDepth = 0;
	StringTree* subTree;

	subTree = new StringTree{};
	tree.subTrees.push_back(subTree);
	len += sub1->Tree(*subTree, subMaxDepth, withPtr);
	maxDepth = max(maxDepth, subMaxDepth);

	subTree = new StringTree{};
	tree.subTrees.push_back(subTree);
	len += sub2->Tree(*subTree, subMaxDepth, withPtr);
	maxDepth = max(maxDepth, subMaxDepth);

	// Display label in the middle
	int totalPadding = len - 2 - this->TreeLabel(withPtr).length();
	assert(totalPadding >= 0);
	int leftPadding = totalPadding / 2;
	tree.s = "(" + string(leftPadding, ' ') + this->TreeLabel(withPtr) + string(totalPadding - leftPadding, ' ') + ")";

	maxDepth++; // Count this term itself
	return len;
}

bool BinaryTerm::ReplaceSubTerm(Term* oldTerm, Term* newTerm)
{
	oldTerm->SetParent(nullptr);
	if (newTerm != nullptr)
		newTerm->SetParent(this);

	if (sub1 == oldTerm)
	{
		sub1 = newTerm;
		return 1;
	}
	else if (sub2 == oldTerm)
	{
		sub2 = newTerm;
		return 1;
	}
	else
	{
		return 0;
	}
}

size_t BinaryTerm::GetNumberOfSubTerms()
{
	return 2;
}
