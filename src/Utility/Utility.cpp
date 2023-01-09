#include "Utility.h"

using namespace std;


void Wait()
{
	cout << "... Press enter to continue." << flush;
	cout << static_cast<char>(27) << static_cast<char>(27);
	char key;
	if (read(STDIN_FILENO, &key, 1) != 1);
	cout << " " << endl;
	//string s;
	//cin >> s;
}
void DebugLog(const string& s)
{
	cout << s;
	Wait();
}
