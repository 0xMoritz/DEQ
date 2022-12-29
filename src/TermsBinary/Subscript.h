/*!
 * @file Subscript.h
 * @brief Contains Binary Term that connects a subscript to a main term
 *
 *  Created on: 2022-12-26
 *      Author: Moritz Geßner
 */

#pragma once

#include "../Term/BinaryTerm.h"


class Subscript : public BinaryTerm
{
public:
	Subscript(Term* _parent, Term* _main, Term* _sub);
	std::string Tex() override;
	std::string Print() override;
};
