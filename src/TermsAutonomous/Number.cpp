#include "Number.h"

using namespace std;

Number::Number(Term* _parent)
: AutonomousTerm(_parent)
{
	treeLabel = "num";
}
string Number::Print()
{
	return to_string(value);
}
string Number::Tex()
{
	return to_string(value);
}
