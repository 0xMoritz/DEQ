#include "FilePrinter.h"

using namespace std;


// class FilePrinter
FilePrinter::FilePrinter(string filename, string header)
: file(outputPath + filename)
{
	//boost::filesystem::create_directories(outputPath); // works only with c++17
	file << header << endl;
}

int FilePrinter::ChangeOutputPath(string newPath)
{
	if (newPath.back()=='/')
		outputPath = newPath;
	else
		outputPath = newPath + "/";

	// https://stackoverflow.com/questions/18100097/portable-way-to-check-if-directory-exists-windows-linux-c
	struct stat info;

	if( stat( outputPath.c_str(), &info ) != 0 )
	{
		// No writing permission
		return 1;
	}
	else if( info.st_mode & S_IFDIR )
	{
		return 0;
	}
	else
	{
		// Directory does not exist
		return 1;
	}
}
string FilePrinter::GetOutputPath()
{
	return outputPath;
};
void FilePrinter::Write(string str)
{
	file << str << endl;
}
void FilePrinter::CloseFile()
{
	file.close();
}
FilePrinter::~FilePrinter()
{

}
