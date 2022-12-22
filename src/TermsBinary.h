/*!
 * @file TermsBinary.h
 * @brief Contains Collection of Terms that have two arguments
 *
 *  Created on: Dec 19, 2022
 *      Author: Moritz Geßner
 */

#pragma once

#include "Term.h"


class Connect2 : public BinaryTerm
{
public:
	Connect2(Term* _parent);
	std::string Print() override;
	std::string Tex() override;
};

class Power : public BinaryTerm
{
public:
	Power(Term* _parent, Term* _base, Term* _exponent);
	std::string Print() override;
	std::string Tex() override;
};

class Subscript : public BinaryTerm
{
public:
	Subscript(Term* _parent, Term* _main, Term* _sub);
	std::string Print() override;
	std::string Tex() override;
};
