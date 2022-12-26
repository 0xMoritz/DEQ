/*!
 * @file TermsSingular.h
 * @brief Contains Collection of Functions that have exactly one argument
 *
 *  Created on: Dec 19, 2022
 *      Author: Moritz Geßner
 */

#pragma once

#include "../Term/SingularTerm.h"


class Brackets : SingularTerm
{
private:
	Term* subTerm;
public:
	Brackets(Term* _parent, Term* _subTerm);
	std::string Print() override;
	std::string Tex() override;
};
