/*!
 * @file Bracket.h
 * @brief Contains class for parantheses
 *
 *  Created on: Dec 26, 2022
 *      Author: Moritz Geßner
 */

#pragma once

#include "../Term/SingularTerm.h"


class Bracket : SingularTerm
{
private:
	Term* subTerm;
public:
	Bracket(Term* _parent, Term* _subTerm);
	std::string Print() override;
	std::string Tex() override;
};
