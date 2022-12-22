#include "TermsBinary.h"

using namespace std;

// class Connect2

Connect2::Connect2(Term* _sub1, Term* _sub2) : BinaryTerm(_sub1, _sub2)
{
	treeLabel = "co2";
}
string Connect2::Print()
{
	return sub1->Print() + sub2->Print();
}
string Connect2::Tex()
{
	return sub1->Tex() + sub2->Tex();
}


// class Power
Power::Power(Term* _base, Term* _exponent) : BinaryTerm(_base, _exponent)
{
	treeLabel = "pow";
	sub2 = _base;
	sub1 = _exponent;
}
string Power::Print()
{
	string s = "";
	s += "(" + sub1->Print() + ")^(" + sub2->Print() + ")";
	return s;
}
string Power::Tex()
{
	string s = "";
	s += "{" + sub1->Tex() + "}^{" + sub2->Tex() + "}";
	return s;
}


// class Subscript
Subscript::Subscript(Term* _main, Term* _sub) : BinaryTerm(_main, _sub)
{
	treeLabel = "sub";
}
string Subscript::Print()
{
	string s = "";
	s += sub1->Print() + "_" + sub2->Print();
	return s;
}
string Subscript::Tex()
{
	string s = "";
	s += "{" + sub1->Tex() + "}_{" + sub2->Tex() + "}";
	return s;
}
