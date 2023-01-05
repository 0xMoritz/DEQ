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
	std::vector<char> symbols; // Contains '*' and ' '
public:
	Multiplication(Term* _parent);
	std::string Tex() override;
	void AppendRight(Term* t, char symbol=' ');
	std::string Print() override;
};
