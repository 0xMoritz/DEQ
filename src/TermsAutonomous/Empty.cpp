#include "Empty.h"

using namespace std;


// class Empty

Empty::Empty(Term* _parent) : AutonomousTerm(_parent)
{
	treeLabel = "0";
}
string Empty::Print()
{
	return s;
}
string Empty::Tex()
{
	return s;
}
