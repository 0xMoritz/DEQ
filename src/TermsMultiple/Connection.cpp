#include "Connection.h"

using namespace std;
using ITERATOR = vector<Term*>::iterator;


Connection::Connection(Term* _parent) : MultiTerm(_parent)
{
	treeLabel = "con";
}
void Connection::AppendRight(Term* t)
{
	subTerms.push_back(t);
	t->SetParent(this);
}
string Connection::Print()
{
	string s;
	if (subTerms.size() > 0)
	{
		for (ITERATOR factor = subTerms.begin(); factor != subTerms.end(); factor++)
		{
			assert(*factor!=nullptr);
			s += (**factor).Print();
		}
		return s;
	}
	return "";
}
string Connection::Tex()
{
	string s;
	if (subTerms.size() > 0)
	{
		for (ITERATOR factor = subTerms.begin(); factor != subTerms.end(); factor++)
		{
			assert(*factor!=nullptr);
			s += (**factor).GetTex();
		}
		return s;
	}
	return "";
}

void Connection::InsertSubTerm(Term* relativeToTerm, Term* newTerm, int relativeIndex)
{
	ITERATOR at = MultiTerm::Find(relativeToTerm);
	assert(relativeIndex == 1 || relativeIndex == 0); // 0: before, 1: after relativeToTerm
	at += relativeIndex;
	assert(at != --subTerms.begin());
	assert(at != ++subTerms.end());
	subTerms.insert(at, newTerm);
	newTerm->SetParent(this);
}


void Connection::RemoveSubTerm(Term* thisOne)
{
	subTerms.erase(MultiTerm::Find(thisOne));
}
