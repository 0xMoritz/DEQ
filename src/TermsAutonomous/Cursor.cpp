#include "Cursor.h"

using namespace std;


Cursor::Cursor(Term* _parent)
: AutonomousTerm(_parent)
{
	treeLabel = "|";
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
	assert(activeCursor!=nullptr);
	return activeCursor;
}
void Cursor::SetActive(Cursor* newActive)
{
	activeCursor = newActive;
}
