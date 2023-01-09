#include "Empty.h"

using namespace std;


// class Empty

Empty::Empty(Term* _parent)
: AutonomousTerm(_parent)
{
	treeLabel = "?";
}
string Empty::Print()
{
	return "?";
}
string Empty::Tex()
{
	return "?";
}
