/*!
 * @file Term.h
 * @brief Basis Class and Derived Classes of Graphalgorithm approach to Mathematical Fomulae
 *
 *  Created on: Dec 19, 2022
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
