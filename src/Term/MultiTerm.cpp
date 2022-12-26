#include "MultiTerm.h"

using namespace std;

// class MultiTerm
MultiTerm::MultiTerm(Term* _parent) : Term(_parent)
{

}

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
