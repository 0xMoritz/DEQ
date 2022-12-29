#include "Subscript.h"

using namespace std;


// class Subscript
Subscript::Subscript(Term* _parent, Term* _main, Term* _sub) : BinaryTerm(_parent, _main, _sub)
{
	treeLabel = "sub";
}
string Subscript::Print()
{
	string s = "";
	assert(sub1!=nullptr);
	assert(sub2!=nullptr);
	s += sub1->Print() + "_" + sub2->Print();
	return s;
}
string Subscript::Tex()
{
	string s = "";
	s += "{" + sub1->GetTex() + "}_{" + sub2->GetTex() + "}";
	return s;
}
