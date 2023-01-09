#include "ColorTerm.h"

using namespace std;


ColorTerm::ColorTerm(Term* _parent, Term* _subTerm, string _color)
: SingularTerm(_parent)
{
	subTerm = _subTerm;
	color = _color;
}

ColorTerm::~ColorTerm()
{

}

std::string ColorTerm::Print()
{
	assert(subTerm!=nullptr);
	return "{" + color + ":" + subTerm->Print() + "}";
}

std::string ColorTerm::Tex()
{
	assert(subTerm!=nullptr);
	return "\\textcolor{" + color + "}{" + subTerm->GetTex() + "}";
}
