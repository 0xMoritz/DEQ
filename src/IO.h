/*!
 * @file DEQ.h
 * @brief Contains Main Function and Console Output commands
 *
 *  Created on: Dec 16, 2022
 *      Author: Moritz Geßner
 */

#pragma once

#include "TermsAutonomous/Cursor.h"
#include "TermsAutonomous/Empty.h"
#include "TermsAutonomous/Number.h"
#include "TermsAutonomous/Raw.h"
#include "TermsAutonomous/Variable.h"
#include "TermsSingular/Bracket.h"
#include "TermsBinary/Connect2.h"
#include "TermsBinary/Power.h"
#include "TermsBinary/Subscript.h"
#include "TermsMultiple/Addition.h"
#include "TermsMultiple/Multiplication.h"
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
