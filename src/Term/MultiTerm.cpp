#include "MultiTerm.h"

using namespace std;
using ITERATOR = vector<Term*>::iterator;

// class MultiTerm
MultiTerm::MultiTerm(Term* _parent) : Term(_parent)
{

}
MultiTerm::~MultiTerm()
{
	//cout << "killing MultiTerm. ";
}

vector<Term*> MultiTerm::GetSubTerms()
{
	return subTerms;
}

int MultiTerm::Tree(StringTree& tree, int& maxDepth)
{
	if (subTerms.size() > 0)
	{
		int len = 0;
		maxDepth = 0;
		for (ITERATOR subTerm = subTerms.begin(); subTerm != subTerms.end(); subTerm++)
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

void MultiTerm::ReplaceSubTerm(Term* newTerm, Term* oldTerm)
{
	if (subTerms.size() > 0)
	{
		oldTerm->SetParent(nullptr);
		newTerm->SetParent(this);

		for (ITERATOR subTerm = subTerms.begin(); subTerm != subTerms.end(); subTerm++)
		{
			if (oldTerm == *subTerm)
			{
				*subTerm = newTerm;
				return;
			}
		}
		throw (string)"Replace method was called in MultiTerm " + PtrAddress(this) + " but Term to replace couldn't be found";
	}
}

size_t MultiTerm::GetNumberOfSubTerms()
{
	return subTerms.size();
}
