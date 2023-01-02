#include "Multiplication.h"

using namespace std;
using ITERATOR = vector<Term*>::iterator;


Multiplication::Multiplication(Term* _parent) : MultiTerm(_parent)
{
	treeLabel = "mul";
}
void Multiplication::Append(Term* t, char symbol)
{
	subTerms.push_back(t);
	symbols.push_back(symbol);
}
string Multiplication::Print()
{
	string s;
	if (subTerms.size() > 0)
	{
		vector<char>::iterator symbol = symbols.begin();
		for (ITERATOR factor = subTerms.begin(); factor != subTerms.end(); factor++, symbol++)
		{
			assert(*factor!=nullptr);
			if (*symbol == '*')
				s += " × ";
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
		vector<char>::iterator symbol = symbols.begin();
		for (ITERATOR factor = subTerms.begin(); factor != subTerms.end(); factor++, symbol++)
		{
			assert(*factor!=nullptr);
			if (*symbol == '*')
				s += "\\times";
			s += (**factor).GetTex();
		}
		return s;
	}
	return "";
}
