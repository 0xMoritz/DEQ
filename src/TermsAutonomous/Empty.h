/*!
 * @file Empty.h
 * @brief Contains class for undefined or empty Term
 *
 *  Created on: 2022-12-26
 *      Author: Moritz Geßner
 */

#pragma once

#include "../Term/AutonomousTerm.h"


class Empty : public AutonomousTerm
{
private:
public:
	Empty(Term* _parent);
	std::string Tex() override;
	std::string Print() override;
};
