/*!
 * @file MultiTerm.h
 * @brief Subclass of Term with an arbitrary number of subTerms
 *
 *  Created on: Dec 26, 2022
 *      Author: Moritz Geßner
 */

#pragma once

#include "Term.h"


class MultiTerm : public Term
{
protected:
	std::list<Term*>* subTerms;
public:
	MultiTerm(Term* _parent);
	int Tree(StringTree& tree, int& maxDepth) override;
};
