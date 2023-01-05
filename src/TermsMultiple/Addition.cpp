#include "Addition.h"

using namespace std;
using ITERATOR = vector<Term*>::iterator;

// class Addition

Addition::Addition(Term* _parent) : MultiTerm(_parent)
{
	treeLabel = "add";
}
void Addition::AppendRight(Term* t, char sign)
{
	subTerms.push_back(t);
	t->SetParent(this);
	signs.push_back(sign);
}
string Addition::Print()
{
	string s;
	if (subTerms.size() > 0)
	{
		vector<char>::iterator sign = signs.begin();
		for (ITERATOR summand = subTerms.begin(); summand != subTerms.end(); summand++, sign++)
		{
			assert(*summand!=nullptr);
			if (*sign != ' ')
				s += ' ' + *sign + ' ';
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
		vector<char>::iterator sign = signs.begin();
		for (ITERATOR summand = ++subTerms.begin(); summand != subTerms.end(); summand++, sign++)
		{
			assert(*summand!=nullptr);
			if (*sign != ' ')
				s += ' ' + *sign + ' ';
			s += (**summand).GetTex();
		}
		return s;
	}
	return "";
}
