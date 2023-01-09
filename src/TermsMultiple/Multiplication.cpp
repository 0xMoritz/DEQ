#include "Multiplication.h"

using namespace std;
using ITERATOR = vector<Term*>::iterator;


Multiplication::Multiplication(Term* _parent)
: MultiTerm(_parent)
{
	treeLabel = "mul";
}
Multiplication::Multiplication(Term* _parent, vector<Term*> _subTerms, vector<char> _symbols)
: MultiTerm(_parent, _subTerms, _symbols)
{
	treeLabel = "mul";
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
			else if (*symbol != ' ')
				throw (string)"Illegal multiplication symbol: '" + string(1, *symbol) + "'";
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
			else if (*symbol != ' ')
				throw (string)"Illegal multiplication symbol: '" + string(1, *symbol) + "'";
			s += (**factor).GetTex();
		}
		return s;
	}
	return "";
}
