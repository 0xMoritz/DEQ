#include "TermsAutonomous.h"

using namespace std;


// class Empty

Empty::Empty()
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
Cursor::Cursor()
{
	treeLabel = "|";
}
string Cursor::Print()
{
	return "|";
}
string Cursor::Tex()
{
	return "|";
}


// class Number
Number::Number(string s)
{
	treeLabel = "num";
	numString = s;
	try
	{
		value = stod(numString);
	}
	catch (...)
	{
		cerr << "[Error] could not parse '" << numString << "' to a number." << endl;
		value = 0;
	}
}
string Number::Print()
{
	return numString;
}
string Number::Tex()
{
	return numString;
}


// class Text
Text::Text(string _text)
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
Variable::Variable(string _name)
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
