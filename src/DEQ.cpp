#include "DEQ.h"

using namespace std;


// TODO: Change from number to raw format, which can be parsed into var, num, fct,...

string FilePrinter::outputPath{"latex/"};
// Static variable Initilization
Cursor* Cursor::activeCursor = nullptr;
Term* Manipulator::rootParent = new Term(nullptr);

int main(int argc, char **argv)
{
	// Learn about pointers:
	//Term* a = new Cursor(nullptr);
	//cout << "typeid: " << typeid(a).name() << ", typeid(a)==typeid(Term*):" << (typeid(a) == typeid(Term*)) << ", typeid(a)==typeid(Cursor*):" << (typeid(a) == typeid(Cursor*)) << ", Termptr: " << (dynamic_cast<Term*>(a)) << ", Cursorptr: " << dynamic_cast<Cursor*>(a) << ", Rawptr" << dynamic_cast<Raw*>(a) << ", nullptr";// << nullptr;




	Manipulator manip;
	Console console(manip);
	console.ShellLoop();
	cout << "Exit." << endl;
	return 0;
}
