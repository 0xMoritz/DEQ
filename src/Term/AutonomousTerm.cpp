#include "AutonomousTerm.h"

using namespace std;


AutonomousTerm::AutonomousTerm(Term* _parent) : Term(_parent)
{

}

int AutonomousTerm::Tree(StringTree& tree, int& maxDepth)
{
	return Term::Tree(tree, maxDepth);
}
