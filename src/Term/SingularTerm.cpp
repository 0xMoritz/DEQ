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

vector<Term*> SingularTerm::GetSubTerms()
{
	return vector<Term*>{sub};
}

Term* SingularTerm::GetSubTerm()
{
	return sub;
}

void SingularTerm::ReplaceSubTerm(Term* oldTerm, Term* newTerm)
{
	if (oldTerm == sub)
	{
		oldTerm->SetParent(nullptr);
		if (newTerm != nullptr)
			newTerm->SetParent(this);
		sub = newTerm;
	}
	else
	{
		throw (string)("Replace method was called in SingularTerm " + PtrAddress(this) + " but Term to replace couldn't be found");
	}
}


int SingularTerm::Tree(StringTree& tree, int& maxDepth, bool withPtr)
{
	//TODO
	throw (string) "error";
}

size_t SingularTerm::GetNumberOfSubTerms()
{
	return 1;
}
