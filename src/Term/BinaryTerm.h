/*!
 * @file BinaryTerm.h
 * @brief Subclass of Term with two subTerms
 *
 *  Created on: Dec 19, 2022
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
	Term* GetSub1();
	void SetSub1(Term* newSub1);
	Term* GetSub2();
	void SetSub2(Term* newSub2);
	int Tree(StringTree& tree, int& maxDepth) override;
};
