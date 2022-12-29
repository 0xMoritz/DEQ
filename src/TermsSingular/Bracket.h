/*!
 * @file Bracket.h
 * @brief Contains class for parantheses
 *
 *  Created on: 2022-12-26
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
	~Bracket();
	std::string Print() override;
	std::string Tex() override;
};
