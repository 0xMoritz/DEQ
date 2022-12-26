#include "Power.h"

using namespace std;

// class Power
Power::Power(Term* _parent, Term* _base, Term* _exponent) : BinaryTerm(_parent, _base, _exponent)
{
	treeLabel = "pow";
	sub2 = _base;
	sub1 = _exponent;
}
string Power::Print()
{
	string s = "";
	assert(sub1!=nullptr);
	assert(sub2!=nullptr);
	s += "(" + sub1->Print() + ")^(" + sub2->Print() + ")";
	return s;
}
string Power::Tex()
{
	string s = "";
	assert(sub1!=nullptr);
	assert(sub2!=nullptr);
	s += "{" + sub1->Tex() + "}^{" + sub2->Tex() + "}";
	return s;
}
