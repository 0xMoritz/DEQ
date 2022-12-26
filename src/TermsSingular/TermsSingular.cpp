#include "TermsSingular.h"

using namespace std;


// class Brackets
Brackets::Brackets(Term* _parent, Term* _subTerm) : SingularTerm(_parent)
{
	subTerm = _subTerm;
}
std::string Brackets::Print()
{
	assert(subTerm!=nullptr);
	return "(" + subTerm->Print() + ")";
}
std::string Brackets::Tex()
{
	assert(subTerm!=nullptr);
	return "\\left(" + subTerm->Tex() + "\\right)";
}
