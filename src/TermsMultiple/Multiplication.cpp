#include "Multiplication.h"

using namespace std;
using ITERATOR = vector<Term*>::iterator;


Multiplication::Multiplication(Term* _parent) : MultiTerm(_parent)
{
	treeLabel = "mul";
}
void Multiplication::Append(Term* t)
{
	subTerms.push_back(t);
}
string Multiplication::Print()
{
	string s;
	if (subTerms.size() > 0)
	{
		s += subTerms.front()->Print();
		for (ITERATOR factor = ++subTerms.begin(); factor != subTerms.end(); factor++)
		{
			assert(*factor!=nullptr);
			if (Term::IsType<Raw>(*factor))
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
	if (subTerms.size() > 0)
	{
		s += subTerms.front()->GetTex();
		for (ITERATOR factor = ++subTerms.begin(); factor != subTerms.end(); factor++)
		{
			assert(*factor!=nullptr);
			if (Term::IsType<Raw>(*factor))
			{
				s+= "\\times";
			}
			s += (**factor).GetTex();
		}
		return s;
	}
	return "";
}
