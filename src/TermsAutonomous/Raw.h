/*!
 * @file Raw.h
 * @brief Contains the class for unparsed Term segments
 *
 *  Created on: Dec 26, 2022
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
	std::string Print() override;
	std::string Tex() override;
	void Append(std::string s);
	std::string Backspace(); // Deletion from right, why not return char? Maybe I want to have certain more complicated structures like a subscript
	std::string Delete(); // Deletion from left
	bool IsEmpty();
};
