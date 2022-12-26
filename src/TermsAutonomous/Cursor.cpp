#include "Cursor.h"

using namespace std;


Cursor::Cursor(Term* _parent) : AutonomousTerm(_parent)
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
	//return "\\hspace{-1.5pt}{\\scriptstyle \\vert}";// TODO: Fine tune hspace  before and after
	return "\\hspace{-1pt}\\raisebox{1.5pt}{{$\\scriptstyle |$}}\\hspace{-1pt}";
	//return "\\hspace{-1.5pt}{\\scalebox{0.6}{\\mbox{\\ensuremath{\\displaystyle |}}}";
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
