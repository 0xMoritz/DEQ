/*!
 * @file TermsAutonomous.h
 * @brief Contains Collection of Autonomous Terms, that is Terms without argument or subterms
 *
 *  Created on: Dec 19, 2022
 *      Author: Moritz Geßner
 */

#pragma once

#include "Term.h"


class Empty : public Term
{
private:
	std::string s;
public:
	Empty();
	std::string Print() override;
	std::string Tex() override;
};

class Cursor : public Term
{
public:
	Cursor();
	std::string Print() override;
	std::string Tex() override;
};

class Number : public Term
{
private:
	double value;
	std::string numString;
public:
	Number(std::string s);
	std::string Print() override;
	std::string Tex() override;
};

class Text : public Term
{
private:
	std::string text;
public:
	Text(std::string _text);
	std::string Print() override;
	std::string Tex() override;
};

class Variable : public Term
{
private:
	std::string name;
public:
	Variable(std::string _name);
	std::string Print() override;
	std::string Tex() override;
};
