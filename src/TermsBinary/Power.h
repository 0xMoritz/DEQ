/*!
 * @file Power.h
 * @brief Contains class for base-exponent relation
 *
 *  Created on: 2022-12-26
 *      Author: Moritz Geßner
 */

#pragma once

#include "../Term/BinaryTerm.h"


class Power : public BinaryTerm
{
public:
	Power(Term* _parent, Term* _base, Term* _exponent);
	std::string Tex() override;
	std::string Print() override;
};
