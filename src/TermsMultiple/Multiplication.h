/*!
 * @file Multiplication.h
 * @brief Contains class for Multiplication of elements
 *
 *  Created on: 2022-12-26
 *      Author: Moritz Geßner
 */

#pragma once

#include "../Term/MultiTerm.h"
#include "../TermsAutonomous/Raw.h"


class Multiplication : public MultiTerm
{
private:
public:
	Multiplication(Term* _parent);
	Multiplication(Term* _parent, std::vector<Term*> _subTerms, std::vector<char> _symbols);
	std::string Tex() override;
	std::string Print() override;
};
