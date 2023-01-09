/*!
 * @file Addition.h
 * @brief Contains class for addition of elements
 *
 *  Created on: 2022-12-26
 *      Author: Moritz Geßner
 */

#pragma once

#include "../Term/MultiTerm.h"
#include "../TermsAutonomous/Raw.h"


class Addition : public MultiTerm
{
private:
public:
	Addition(Term* _parent);
	Addition(Term* _parent, std::vector<Term*> _subTerms, std::vector<char> _symbols);
	std::string Tex() override;
	std::string Print() override;
};
