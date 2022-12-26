/*!
 * @file TermsMultiple.h
 * @brief Contains Collection of Functions that have an arbitrar amount of arguments
 *
 *  Created on: Dec 19, 2022
 *      Author: Moritz Geßner
 */

#pragma once

#include "../Term/MultiTerm.h"
#include "../TermsAutonomous/TermsAutonomous.h"


class Addition : public MultiTerm
{
public:
	Addition(Term* _parent, std::list<Term*>* _subTerms);
	void Append(Term* t);
	std::string Print() override;
	std::string Tex() override;
};


class Multiplication : public MultiTerm
{
public:
	Multiplication(Term* _parent, std::list<Term*>* _subTerms);
	void Append(Term* t);
	std::string Print() override;
	std::string Tex() override;
};
