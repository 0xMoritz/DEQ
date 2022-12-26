#include "Bracket.h"

using namespace std;


Bracket::Bracket(Term* _parent, Term* _subTerm) : SingularTerm(_parent)
{
	subTerm = _subTerm;
}
std::string Bracket::Print()
{
	assert(subTerm!=nullptr);
	return "(" + subTerm->Print() + ")";
}
std::string Bracket::Tex()
{
	assert(subTerm!=nullptr);
	return "\\left(" + subTerm->Tex() + "\\right)";
}
