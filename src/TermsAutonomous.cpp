#include "TermsAutonomous.h"

using namespace std;


// class Empty

Empty::Empty(Term* _parent) : Term(_parent)
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

// class Cursor
Cursor::Cursor(Term* _parent) : Term(_parent)
{
	treeLabel = "|";
	left = nullptr;
	right = nullptr;
}
string Cursor::Print()
{
	return "|";
}
string Cursor::Tex()
{
	return "\\vspace{-0.5pt}\\mid";
}
Cursor* Cursor::GetActive()
{
	return activeCursor;
}
void Cursor::SetActive(Cursor* newActive)
{
	activeCursor = newActive;
}
Term* Cursor::GetLeft()
{
	return left;
}
void Cursor::SetLeft(Term* newLeft)
{
	left = newLeft;
}
Term* Cursor::GetRight()
{
	return right;
}
void Cursor::SetRight(Term* newRight)
{
	right = newRight;
}


// class Number
Number::Number(Term* _parent) : Term(_parent)
{
	treeLabel = "num";
	numString = "";
}
// This will be usefull later
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
string Number::Print()
{
	return numString;
}
string Number::Tex()
{
	return numString;
}
void Number::AppendDigit(int digit)
{
	numString += to_string(digit);
}
void Number::BackspaceDigit()
{
	assert(numString.length() > 0);
	numString = numString.substr(0, numString.length()-1);
}
void Number::DeleteDigit()
{
	assert(numString.length() > 0);
	numString = numString.substr(1, numString.length()-1);
}
bool Number::IsEmpty()
{
	if (numString.length() == 0)
		return 1;
	return 0;
}


// class Text
Text::Text(Term* _parent, string _text) : Term(_parent)
{
	treeLabel = "txt";
	text = _text;
}
string Text::Print()
{
	return text;
}
string Text::Tex()
{
	return text;
}


// class Variable
Variable::Variable(Term* _parent, string _name) : Term(_parent)
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
