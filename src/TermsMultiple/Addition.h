/*!
 * @file Addition.h
 * @brief Contains class for addition of elements
 *
 *  Created on: Dec 26, 2022
 *      Author: Moritz Geßner
 */

#pragma once

#include "../Term/MultiTerm.h"
#include "../TermsAutonomous/Raw.h"


class Addition : public MultiTerm
{
public:
	Addition(Term* _parent, std::list<Term*>* _subTerms);
	void Append(Term* t);
	std::string Print() override;
	std::string Tex() override;
};
