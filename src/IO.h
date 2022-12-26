/*!
 * @file DEQ.h
 * @brief Contains Main Function and Console Output commands
 *
 *  Created on: Dec 16, 2022
 *      Author: Moritz Geßner
 */

#pragma once

#include "TermsAutonomous/TermsAutonomous.h"
#include "TermsSingular/TermsSingular.h"
#include "TermsBinary/TermsBinary.h"
#include "TermsMultiple/TermsMultiple.h"
#include "Utility/FilePrinter.h"

class IO
{
private:
public:
	std::string debugText = "";
	IO();
	void InsertDigit(Term*& t, int digit);
	void Backspace(Term*& t);
	void Delete(Term*& t);
	int Latex(Term*& t);
};
