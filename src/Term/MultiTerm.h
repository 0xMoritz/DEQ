/*!
 * @file MultiTerm.h
 * @brief Subclass of Term with an arbitrary number of subTerms
 *
 *  Created on: 2022-12-26
 *      Author: Moritz Geßner
 */

#pragma once

#include "Term.h"


class MultiTerm : public Term
{
protected:
	std::vector<Term*> subTerms;
	std::vector<Term*>::iterator Find(Term* t);
public:
	MultiTerm(Term* _parent);
	virtual ~MultiTerm();
	std::vector<Term*> GetSubTerms() override;
	int Tree(StringTree& tree, int& maxDepth, bool withPtr=false) override;
	bool ReplaceSubTerm(Term* oldTerm, Term* newTerm) override;
	size_t GetNumberOfSubTerms()	override;
};
