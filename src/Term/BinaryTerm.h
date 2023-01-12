/*!
 * @file BinaryTerm.h
 * @brief Subclass of Term with two subTerms
 *
 *  Created on: 2022-12-26
 *      Author: Moritz Geßner
 */

#pragma once

#include "Term.h"


class BinaryTerm : public Term
{
protected:
	Term* sub1;
	Term* sub2;
public:
	BinaryTerm(Term* _parent);
	BinaryTerm(Term* _parent, Term* _sub1, Term* _sub2);
	virtual ~BinaryTerm();
	std::vector<Term*> GetSubTerms() override;
	Term* GetSub1();
	void SetSub1(Term* newSub1);
	Term* GetSub2();
	void SetSub2(Term* newSub2);
	int Tree(StringTree& tree, int& maxDepth, bool withPtr=false) override;
	bool ReplaceSubTerm(Term* oldTerm, Term* newTerm) override;
	bool RemoveSubTerm(Term* t) override;
	size_t GetNumberOfSubTerms() override;
};
