#include "Addition.h"

using namespace std;
using ITERATOR = vector<Term*>::iterator;

// class Addition

Addition::Addition(Term* _parent)
: MultiTerm(_parent)
{
	treeLabel = "add";
}
Addition::Addition(Term* _parent, vector<Term*> _subTerms, vector<char> _symbols)
: MultiTerm(_parent, _subTerms, _symbols)
{
	treeLabel = "add";
}
string Addition::Print()
{
	string s;
	if (subTerms.size() > 0)
	{
		vector<char>::iterator symbol = symbols.begin();
		for (ITERATOR summand = subTerms.begin(); summand != subTerms.end(); summand++, symbol++)
		{
			assert(*summand!=nullptr);
			if (*symbol != ' ')
				s += *symbol;
			s += (**summand).Print();
		}
		return s;
	}
	return "";
}
string Addition::Tex()
{
	string s;
	if (subTerms.size() > 0)
	{
		vector<char>::iterator symbol = symbols.begin();
		for (ITERATOR summand = subTerms.begin(); summand != subTerms.end(); summand++, symbol++)
		{
			assert(*summand!=nullptr);
			if (*symbol != ' ')
				s += " + ";
			s += (**summand).GetTex();
		}
		return s;
	}
	return "";
}
