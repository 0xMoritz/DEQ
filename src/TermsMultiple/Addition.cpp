#include "Addition.h"

using namespace std;

// class Addition

Addition::Addition(Term* _parent) : MultiTerm(_parent)
{
	treeLabel = "add";
}
void Addition::Append(Term* t)
{
	subTerms.push_back(t);
}
string Addition::Print()
{
	string s;
	if (subTerms.size() > 0)
	{
		s += subTerms.front()->Print();
		for (auto summand = ++subTerms.begin(); summand != subTerms.end(); summand++)
		{
			assert(*summand!=nullptr);
			s += " + " + (**summand).Print();
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
		s += subTerms.front()->Tex();
		for (auto summand = ++subTerms.begin(); summand != subTerms.end(); summand++)
		{
			assert(*summand!=nullptr);
			s += " + " + (**summand).Tex();
		}
		return s;
	}
	return "";
}
