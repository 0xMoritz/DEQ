/*!
 * @file Term.h
 * @brief Basis Class and Derived Classes of Graphalgorithm approach to Mathematical Fomulae
 *
 *  Created on: 2022-12-19
 *      Author: Moritz Geßner
 */

#pragma once

#include "../Utility/StringTree.h"
#include "../Utility/Utility.h"


class Term
{
protected:
	Term* parent;
	std::string treeLabel = "err";


	static std::string PtrAddress(Term* ptr);
public:
	//~Term() = default;
	Term(Term* _parent);
	virtual ~Term();
	Term* GetParent();
	void SetParent(Term* newParent);
	std::string GetTex();

	virtual std::string Tex();
	virtual std::vector<Term*> GetSubTerms();
	virtual Term Derivative();
	virtual std::string Print();
	virtual int Tree(StringTree& tree, int& maxDepth);
	virtual void ReplaceSubTerm(Term* oldTerm, Term* newTerm);
	virtual size_t GetNumberOfSubTerms();

	static Term* WithoutCursor(Term* t);
};
