/*!
 * @file Power.h
 * @brief Contains class for base-exponent relation
 *
 *  Created on: Dec 26, 2022
 *      Author: Moritz Geßner
 */

#pragma once

#include "../Term/BinaryTerm.h"


class Power : public BinaryTerm
{
public:
	Power(Term* _parent, Term* _base, Term* _exponent);
	std::string Print() override;
	std::string Tex() override;
};
