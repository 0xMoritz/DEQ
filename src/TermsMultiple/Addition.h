/*!
 * @file Addition.h
 * @brief Contains class for addition of elements
 *
 *  Created on: 2022-12-26
 *      Author: Moritz Geßner
 */

#pragma once

#include "../Term/MultiTerm.h"
#include "../TermsAutonomous/Raw.h"


class Addition : public MultiTerm
{
	// Cursor positions should be 
private:
	std::vector<char> signs; // should be either signs '+', '-' or ' ' (for first summand)
public:
	Addition(Term* _parent);
	void AppendRight(Term* t, char sign);
	std::string Tex() override;
	std::string Print() override;
};
