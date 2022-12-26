/*!
 * @file AutonomousTerm.h
 * @brief Subclass of Term without subTerms
 *
 *  Created on: Dec 26, 2022
 *      Author: Moritz Geßner
 */

#pragma once

#include "Term.h"


class AutonomousTerm : public Term
{
protected:
public:
	AutonomousTerm(Term* _parent);
	int Tree(StringTree& tree, int& maxDepth) override;
};
