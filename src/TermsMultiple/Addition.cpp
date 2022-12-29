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
		s += subTerms.front()->GetTex();
		for (auto summand = ++subTerms.begin(); summand != subTerms.end(); summand++)
		{
			assert(*summand!=nullptr);
			s += " + " + (**summand).GetTex();
		}
		return s;
	}
	return "";
}
