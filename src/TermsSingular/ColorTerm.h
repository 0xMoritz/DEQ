/*!
 * @file Bracket.h
 * @brief Contains class for parantheses
 *
 *  Created on: 2022-12-26
 *      Author: Moritz Geßner
 */

#pragma once

#include "../Term/SingularTerm.h"


class ColorTerm : SingularTerm
{
private:
	Term* subTerm;
	std::string color;
public:
	ColorTerm(Term* _parent, Term* _subTerm, std::string _color);
	~ColorTerm();
	std::string Tex() override;
	std::string Print() override;
};
