#include "Variable.h"

using namespace std;


Variable::Variable(Term* _parent, string _name)
: AutonomousTerm(_parent)
{
	treeLabel = "var";
	name = _name;
}
string Variable::Print()
{
	return name;
}
string Variable::Tex()
{
	return name;
}
