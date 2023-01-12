#include "MultiTerm.h"

using namespace std;
using ITERATOR = vector<Term*>::iterator;

// class MultiTerm
MultiTerm::MultiTerm(Term* _parent)
: Term(_parent)
{ }
MultiTerm::MultiTerm(Term* _parent, vector<Term*> _subTerms, vector<char> _symbols) : Term(_parent), subTerms(_subTerms), symbols(_symbols)
{
	for (vector<Term*>::iterator it = subTerms.begin(); it != subTerms.end(); it++)
	{
		(*it)->SetParent(this);
	}
}
MultiTerm::~MultiTerm()
{
	//cout << "killing MultiTerm. ";
}

vector<Term*> MultiTerm::GetSubTerms()
{
	return subTerms;
}

bool MultiTerm::FindSubTerm(Term* t, vector<Term*>::iterator& tIt)
{
	tIt = subTerms.begin();
	for (; tIt != subTerms.end(); tIt++)
	{
		if (*tIt == t)
		{
			return 1;
		}
	}
	return 0;
}

bool MultiTerm::FindWithSymbol(Term* t, vector<Term*>::iterator& tIt, vector<char>::iterator& sIt)
{
	tIt = subTerms.begin();
	sIt = symbols.begin();
	for (; tIt != subTerms.end(); tIt++, sIt++)
	{
		if (*tIt == t)
		{
			return 1;
		}
	}
	return 0;
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
		//if (newTerm != nullptr) // Alread happens in InsertSubTerm
		//	newTerm->SetParent(this);


		// Find oldTerm and replace
		vector<char>::iterator sIt; // old symbol
		vector<Term*>::iterator tIt; //
		FindWithSymbol(oldTerm, tIt, sIt);
		InsertSubTerm(oldTerm, newTerm, 0, *sIt);
		RemoveSubTerm(oldTerm);
		/*for (ITERATOR subTerm = subTerms.begin(); subTerm != subTerms.end(); subTerm++)
		{
			if (oldTerm == *subTerm)
			{
				*subTerm = newTerm;
				return 1;
			}
		}*/
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
	DebugLog("SettingParentof " + Term::PtrAddress(t));
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

void MultiTerm::InsertSubTerm(Term* relativeToTerm, Term* newTerm, int relativeIndex, char symbol)
{
	vector<char>::iterator sIt;
	vector<Term*>::iterator tIt;
	MultiTerm::FindWithSymbol(relativeToTerm, tIt, sIt);
	assert(relativeIndex == 1 || relativeIndex == 0); // 0: before, 1: after relativeToTerm
	tIt += relativeIndex;
	sIt += relativeIndex;
	assert(tIt != --subTerms.begin());
	assert(tIt != ++subTerms.end());
	subTerms.insert(tIt, newTerm);
	symbols.insert(sIt, symbol);
	newTerm->SetParent(this);
}

bool MultiTerm::RemoveSubTerm(Term* t)
{
	vector<char>::iterator sIt;
	vector<Term*>::iterator tIt;
	bool found = MultiTerm::FindWithSymbol(t, tIt, sIt);
	if (found)
	{
		subTerms.erase(tIt);
		symbols.erase(sIt);
	}
	return found;
}
