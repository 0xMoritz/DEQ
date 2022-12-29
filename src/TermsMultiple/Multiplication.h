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
public:
	Multiplication(Term* _parent);
	void Append(Term* t);
	std::string Print() override;
	std::string Tex() override;
};
