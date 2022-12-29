/*!
 * @file Number.h
 * @brief Contains class for a number with a definite value
 *
 *  Created on: 2022-12-26
 *      Author: Moritz Geßner
 */

#pragma once

#include "../Term/AutonomousTerm.h"

class Number : public AutonomousTerm
{
private:
	double value;
public:
	Number(Term* _parent);
	std::string Print() override;
	std::string Tex() override;
	bool IsEmpty();
	//Term* ToRaw() ??
	//bool IsZero() ??
};
