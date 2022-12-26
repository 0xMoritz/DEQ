#include "Raw.h"

using namespace std;


Raw::Raw(Term* _parent) : AutonomousTerm(_parent)
{
	treeLabel = "raw";
	text = "";
}
// This might be usefull later
/*
try
{
	value = stod(numString);
}
catch (...)
{
	cerr << "[Error] could not parse '" << numString << "' to a number." << endl;
	value = 0;
}
*/
string Raw::Print()
{
	return text;
}
string Raw::Tex()
{
	return text;
}
void Raw::Append(string s)
{
	text += s;
}
void Raw::Backspace()
{
	assert(text.length() > 0); // This case should be filtered by isEmpty checks
	text = text.substr(0, text.length()-1);
}
void Raw::Delete()
{
	assert(text.length() > 0); // This case should be filtered by isEmpty checks
	text = text.substr(1, text.length()-1);
}
bool Raw::IsEmpty()
{
	if (text.length() == 0)
		return 1;
	return 0;
}
