/*!
 * @file FilePrinter.h
 * @brief Auxillary class to write data into a .csv file
 * copied from thesis
 *
 *  Created on: 2022-12-20
 *      Author: Moritz Geßner
 */

#pragma once

#include "global.h"


/*! \brief Object for writing content to a file.
 *
 * A Printer Object is bound to one file, that should be closed before destruction.
 * Contents can be passed as vectors (or plain text) and will be written as one line of a .csv file.
 */
class FilePrinter
{
private:
	static std::string outputPath; //!< The path all files will be saved to, can be changed with @ref ChangeOutputPath
	std::ofstream file; //!< opened file

public:
	/*!
	 * Constructor for Printer Object, opens a file with \p filename. \p header will
	 * be written to the first line of the file.
	 * \param filename name of the file, will be saved in directory @ref outputPath
	 * \param header first line of the file
	 */
	FilePrinter(std::string filename, std::string header="");

	/*!
	 * Changes the global output path to \p newPath
	 * \return 1 if the directory doesn't exist or can't be accessed, 0 if the directory exist and is writeable
	 */
	static int ChangeOutputPath(std::string newPath);

	/*!
	 * Returns the global output Path
	 */
	static std::string GetOutputPath();

	/*!
	 * Writes a custom message \p str to the file.
	 */
	void Write(std::string str);

	/*!
	 * Closes the file. Should be called before destructor
	 */
	void CloseFile();

	/*!
	 * Does not call @ref CloseFile
	 */
	~FilePrinter();
};
