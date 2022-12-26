#include "DEQ.h"

using namespace std;


// TODO: Change from number to raw format, which can be parsed into var, num, fct,...

string FilePrinter::outputPath{"latex/"};
// Static variable Initilization
Cursor* Cursor::activeCursor = nullptr;

int main(int argc, char **argv)
{
	Manipulator manip;
	Console console(manip);
	console.ShellLoop();
	cout << "Exit." << endl;
	return 0;
}
