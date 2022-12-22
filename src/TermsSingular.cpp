#include "TermsSingular.h"

using namespace std;


// class Brackets
Brackets::Brackets(Term* _subTerm)
{
	subTerm = _subTerm;
}
std::string Brackets::Print()
{
	return "(" + subTerm->Print() + ")";
}
std::string Brackets::Tex()
{
	return "\\left(" + subTerm->Tex() + "\\right)";
}
