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

int AutonomousTerm::Tree(StringTree& tree, int& maxDepth, bool withPtr)
{
	maxDepth = 1;
	// return value is length of string
	tree.s = "(" + TreeLabel(withPtr) + ")";
	return TreeLabel(withPtr).length() + 2;
}

void AutonomousTerm::ReplaceSubTerm(Term* newTerm, Term* oldTerm)
{

}

size_t AutonomousTerm::GetNumberOfSubTerms()
{
	return 0;
}
