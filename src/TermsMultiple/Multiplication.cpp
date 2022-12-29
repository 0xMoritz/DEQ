#include "Multiplication.h"

using namespace std;


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
		for (auto factor = ++subTerms.begin(); factor != subTerms.end(); factor++)
		{
			assert(*factor!=nullptr);
			if (typeid(**factor) == typeid(Raw))
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
		for (auto factor = ++subTerms.begin(); factor != subTerms.end(); factor++)
		{
			assert(*factor!=nullptr);
			if (typeid(**factor) == typeid(Raw))
			{
				s+= "\\times";
			}
			s += (**factor).GetTex();
		}
		return s;
	}
	return "";
}
