/*!
 * @file Variable.h
 * @brief Contains class Variable, that describes a certain object to solve or differentiate by
 *
 *  Created on: Dec 26, 2022
 *      Author: Moritz Geßner
 */

#pragma once

#include "../Term/AutonomousTerm.h"


class Variable : public AutonomousTerm
{
private:
	std::string name;
public:
	Variable(Term* _parent, std::string _name);
	std::string Print() override;
	std::string Tex() override;
};