/*!
 * @file SingularTerm.h
 * @brief Subclass of Term with one subTerm
 *
 *  Created on: 2022-12-26
 *      Author: Moritz Geßner
 */

#pragma once

#include "Term.h"


class SingularTerm : public Term
{
protected:
	Term* sub = nullptr;
public:
	SingularTerm(Term* _parent);
	virtual ~SingularTerm();
	std::vector<Term*> GetSubTerms() override;
	Term* GetSubTerm();
	bool ReplaceSubTerm(Term* oldTerm, Term* newTerm) override;
	int Tree(StringTree& tree, int& maxDepth, bool withPtr=false);
	size_t GetNumberOfSubTerms() override;
};
