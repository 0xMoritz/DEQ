#include "SingularTerm.h"

using namespace std;

// class SingularTerm
SingularTerm::SingularTerm(Term* _parent) : Term(_parent)
{

}

SingularTerm::~SingularTerm()
{
	//cout << "killing SingularTerm. ";
}

list<Term*> SingularTerm::GetSubTerms()
{
	return list<Term*>{sub};
}

void SingularTerm::ReplaceSubTerm(Term* oldTerm, Term* newTerm)
{
	if (oldTerm == sub)
	{
		oldTerm->SetParent(nullptr);
		newTerm->SetParent(this);
		sub = newTerm;
	}
	else
	{
		throw (string)("Replace method was called in SingularTerm " + PtrAddress(this) + " but Term to replace couldn't be found");
	}
}
