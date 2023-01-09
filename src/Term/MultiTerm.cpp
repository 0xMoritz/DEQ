#include "MultiTerm.h"

using namespace std;
using ITERATOR = vector<Term*>::iterator;

// class MultiTerm
MultiTerm::MultiTerm(Term* _parent)
: Term(_parent)
{ }
MultiTerm::MultiTerm(Term* _parent, vector<Term*> _subTerms, vector<char> _symbols) : Term(_parent), subTerms(_subTerms), symbols(_symbols)
{ }
MultiTerm::~MultiTerm()
{
	//cout << "killing MultiTerm. ";
}

vector<Term*> MultiTerm::GetSubTerms()
{
	return subTerms;
}

vector<Term*>::iterator MultiTerm::Find(Term* t)
{
	ITERATOR it = subTerms.begin();
	for (; it != subTerms.end(); it++)
	{
		if (*it == t)
			return it;
	}
	throw (string)"Term not Found.";
}

int MultiTerm::Tree(StringTree& tree, int& maxDepth, bool withPtr)
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
			len += (**subTerm).Tree(*subTree, subMaxDepth, withPtr);
			maxDepth = max(maxDepth, subMaxDepth);
		}
		// Display label in the middle
		int totalPadding = len - 2 - this->TreeLabel(withPtr).length();
		assert(totalPadding >= 0);
		int leftPadding = totalPadding / 2;
		tree.s = "(" + string(leftPadding, ' ') + this->TreeLabel(withPtr) + string(totalPadding - leftPadding, ' ') + ")";

		maxDepth++; // Count this term itself
		return len;
	}
	return Term::Tree(tree, maxDepth, withPtr);
}

bool MultiTerm::ReplaceSubTerm(Term* oldTerm, Term* newTerm)
{
	if (subTerms.size() > 0)
	{
		// Set links
		oldTerm->SetParent(nullptr);
		if (newTerm != nullptr)
			newTerm->SetParent(this);

		// Find oldTerm and replace
		for (ITERATOR subTerm = subTerms.begin(); subTerm != subTerms.end(); subTerm++)
		{
			if (oldTerm == *subTerm)
			{
				*subTerm = newTerm;
				return 1;
			}
		}
	}
	return 0;
}

size_t MultiTerm::GetNumberOfSubTerms()
{
	return subTerms.size();
}


void MultiTerm::AppendRight(Term* t, char symbol)
{
	t->SetParent(this);
	subTerms.push_back(t);
	symbols.push_back(symbol);
}
void MultiTerm::AppendLeft(Term* t, char symbol)
{
	t->SetParent(this);
	subTerms.insert(subTerms.begin(), t);
	symbols.insert(symbols.begin(), symbol);
}

vector<char> MultiTerm::GetSymbols()
{
	return symbols;
}

vector<Term*>::iterator MultiTerm::FindWithSymbol(Term* t, vector<char>::iterator& sIt)
{
	vector<Term*>::iterator it = subTerms.begin();
	sIt = symbols.begin();
	for (; it != subTerms.end(); it++, sIt++)
	{
		if (*it == t)
		{
			return it;
		}
	}
	throw (string)"Term not Found.";
}


void MultiTerm::InsertSubTerm(Term* relativeToTerm, Term* newTerm, int relativeIndex, char symbol)
{
	vector<char>::iterator sIt;
	ITERATOR at = MultiTerm::FindWithSymbol(relativeToTerm, sIt);
	assert(relativeIndex == 1 || relativeIndex == 0); // 0: before, 1: after relativeToTerm
	at += relativeIndex;
	sIt += relativeIndex;
	assert(at != --subTerms.begin());
	assert(at != ++subTerms.end());
	subTerms.insert(at, newTerm);
	symbols.insert(sIt, symbol);
	newTerm->SetParent(this);
}

void MultiTerm::RemoveSubTerm(Term* thisOne)
{
	vector<char>::iterator sIt;
	ITERATOR at = MultiTerm::FindWithSymbol(thisOne, sIt);
	subTerms.erase(at);
	symbols.erase(sIt);
}
