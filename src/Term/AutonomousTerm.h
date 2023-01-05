/*!
 * @file AutonomousTerm.h
 * @brief Subclass of Term without subTerms
 *
 *  Created on: 2022-12-26
 *      Author: Moritz Geßner
 */

#pragma once

#include "Term.h"


class AutonomousTerm : public Term
{
protected:
public:
	AutonomousTerm(Term* _parent);
	virtual ~AutonomousTerm();
	std::vector<Term*> GetSubTerms() override;
	int Tree(StringTree& tree, int& maxDepth, bool withPtr=false) override;
	bool ReplaceSubTerm(Term* oldTerm, Term* newTerm) override;
	size_t GetNumberOfSubTerms() override;
};
