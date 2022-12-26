/*!
 * @file Term.h
 * @brief Basis Class and Derived Classes of Graphalgorithm approach to Mathematical Fomulae
 *
 *  Created on: Dec 19, 2022
 *      Author: Moritz Geßner
 */

#pragma once

#include "../Utility/StringTree.h"


class Term
{
protected:
	Term* parent;
	std::string treeLabel = "err";
public:
	//~Term() = default;
	Term(Term* _parent);
	Term* GetParent();
	void SetParent(Term* newParent);

	virtual Term Derivative();
	virtual std::string Print();
	virtual std::string Tex();
	virtual int Tree(StringTree& tree, int& maxDepth);

	static Term* WithoutCursor(Term* t);
};
