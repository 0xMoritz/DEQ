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
public:
	Addition(Term* _parent);
	void Append(Term* t);
	std::string Print() override;
	std::string Tex() override;
};
