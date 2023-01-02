#include "Raw.h"

using namespace std;


Raw::Raw(Term* _parent) : AutonomousTerm(_parent)
{
	treeLabel = "raw";
	text = "";
}

Raw::~Raw()
{
	//cout << "killing raw. ";
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
void Raw::AppendRight(string s)
{
	text = text + s;
}
void Raw::AppendLeft(string s)
{
	text = s + text;
}
std::string Raw::Backspace()
{
	assert(text.length() > 0); // This case should be filtered by isEmpty checks
	string deleted = text.substr(text.length()-1, 1);
	text = text.substr(0, text.length()-1);
	return deleted;
}
std::string Raw::Delete()
{
	assert(text.length() > 0); // This case should be filtered by isEmpty checks
	string deleted = text.substr(0, 1);
	text = text.substr(1, text.length()-1);
	return deleted;
}
bool Raw::IsEmpty()
{
	if (text.length() == 0)
		return 1;
	return 0;
}
