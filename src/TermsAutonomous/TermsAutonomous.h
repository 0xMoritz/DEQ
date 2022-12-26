/*!
 * @file TermsAutonomous.h
 * @brief Contains Collection of Autonomous Terms, that is Terms without argument or subterms
 *
 *  Created on: Dec 19, 2022
 *      Author: Moritz Geßner
 */

#pragma once

#include "../Term/AutonomousTerm.h"


class Empty : public Term
{
private:
	std::string s;
public:
	Empty(Term* _parent);
	std::string Print() override;
	std::string Tex() override;
};

class Cursor : public Term
{
private:
	Term* left;
	Term* right;
	static Cursor* activeCursor; // I suppose it might be usefull to have more than one cursor, to store in not actively editing equations for instance, but only one cursor should be capable of writing active input.
public:
	Cursor(Term* _parent);
	std::string Print() override;
	std::string Tex() override;
	Term* GetLeft();
	void SetLeft(Term* newLeft);
	Term* GetRight();
	void SetRight(Term* newRight);

	static Cursor* GetActive();
	static void SetActive(Cursor* newActive);
};

class Number : public Term
{
private:
	double value;
	std::string numString;
public:
	Number(Term* _parent);
	std::string Print() override;
	std::string Tex() override;
	void AppendDigit(int digit);
	void BackspaceDigit(); // Deletion from right
	void DeleteDigit(); // Deletion from left
	bool IsEmpty();
};

class Text : public Term
{
private:
	std::string text;
public:
	Text(Term* _parent, std::string _text);
	std::string Print() override;
	std::string Tex() override;
};

class Variable : public Term
{
private:
	std::string name;
public:
	Variable(Term* _parent, std::string _name);
	std::string Print() override;
	std::string Tex() override;
};
