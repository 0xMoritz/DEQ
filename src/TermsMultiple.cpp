#include "TermsMultiple.h"

using namespace std;

// class Addition

Addition::Addition(list<Term*>* _subTerms)
{
	treeLabel = "add";
	subTerms = _subTerms;
}
void Addition::Append(Term* t)
{
	subTerms->push_back(t);
}
string Addition::Print()
{
	string s;
	if (subTerms->size() > 0)
	{
		s += subTerms->front()->Print();
		for (auto summand = ++subTerms->begin(); summand != subTerms->end(); summand++)
		{
			s += " + " + (**summand).Print();
		}
		return s;
	}
	return "";
}
string Addition::Tex()
{
	string s;
	if (subTerms->size() > 0)
	{
		s += subTerms->front()->Tex();
		for (auto summand = ++subTerms->begin(); summand != subTerms->end(); summand++)
		{
			s += " + " + (**summand).Tex();
		}
		return s;
	}
	return "";
}


// class Addition

Multiplication::Multiplication(list<Term*>* _subTerms)
{
	treeLabel = "mul";
	subTerms = _subTerms;
}
void Multiplication::Append(Term* t)
{
	subTerms->push_back(t);
}
string Multiplication::Print()
{
	string s;
	if (subTerms->size() > 0)
	{
		s += subTerms->front()->Print();
		for (auto factor = ++subTerms->begin(); factor != subTerms->end(); factor++)
		{
			if (typeid(**factor) == typeid(Number))
			{
				s+= "×";
			}
			s += (**factor).Print();
		}
		return s;
	}
	return "";
}
string Multiplication::Tex()
{
	string s;
	if (subTerms->size() > 0)
	{
		s += subTerms->front()->Tex();
		for (auto factor = ++subTerms->begin(); factor != subTerms->end(); factor++)
		{
			if (typeid(**factor) == typeid(Number))
			{
				s+= "\\times";
			}
			s += (**factor).Tex();
		}
		return s;
	}
	return "";
}
