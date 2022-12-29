/*!
 * @file Variable.h
 * @brief Contains class Variable, that describes a certain object to solve or differentiate by
 *
 *  Created on: 2022-12-26
 *      Author: Moritz Geßner
 */

#pragma once

#include "../Term/AutonomousTerm.h"


class Variable : public AutonomousTerm
{
private:
	std::string name;
public:
	std::string Tex() override;
	Variable(Term* _parent, std::string _name);
	std::string Print() override;
};
