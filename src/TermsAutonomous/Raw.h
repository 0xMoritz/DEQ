/*!
 * @file Raw.h
 * @brief Contains the class for unparsed Term segments
 *
 *  Created on: 2022-12-26
 *      Author: Moritz Geßner
 */

#pragma once

#include "../Term/AutonomousTerm.h"

class Raw : public AutonomousTerm
{
private:
	std::string text;
public:
	Raw(Term* _parent);
	~Raw();
	std::string Tex() override;
	std::string Print() override;
	void AppendRight(std::string s);
	void AppendLeft(std::string s);
	std::string BackspaceContent(); // Deletion from right, why not return char? Maybe I want to have certain more complicated structures like a subscript
	std::string DelContent(); // Deletion from left
	bool IsEmpty();
};
