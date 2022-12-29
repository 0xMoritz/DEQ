#include "AutonomousTerm.h"

using namespace std;


AutonomousTerm::AutonomousTerm(Term* _parent) : Term(_parent)
{

}

AutonomousTerm::~AutonomousTerm()
{
	//cout << "killing AutonomousTerm. " << endl;
}

vector<Term*> AutonomousTerm::GetSubTerms()
{
	return vector<Term*>{};
}

int AutonomousTerm::Tree(StringTree& tree, int& maxDepth)
{
	return Term::Tree(tree, maxDepth);
}

void AutonomousTerm::ReplaceSubTerm(Term* newTerm, Term* oldTerm)
{
	throw (string)"Replace has been called on AutonomousTerm" + PtrAddress(this);
}

size_t AutonomousTerm::GetNumberOfSubTerms()
{
	return 0;
}
