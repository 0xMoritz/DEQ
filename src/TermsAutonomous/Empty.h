/*!
 * @file Empty.h
 * @brief Contains class for undefined or empty Term
 *
 *  Created on: Dec 26, 2022
 *      Author: Moritz Geßner
 */

#pragma once

#include "../Term/AutonomousTerm.h"


class Empty : public AutonomousTerm
{
private:
	std::string s;
public:
	Empty(Term* _parent);
	std::string Print() override;
	std::string Tex() override;
};
