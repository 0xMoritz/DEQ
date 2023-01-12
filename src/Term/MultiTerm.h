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
	std::vector<char> symbols; // Contains '*' and ' ' for Multiplication and '+' or '-' or ' '(leading Term) for addition
public:
	MultiTerm(Term* _parent);
	MultiTerm(Term* _parent, std::vector<Term*> _subTerms, std::vector<char> _symbols);
	virtual ~MultiTerm();
	bool FindSubTerm(Term* t, std::vector<Term*>::iterator&);
	bool FindWithSymbol(Term* t, std::vector<Term*>::iterator& tIt, std::vector<char>::iterator& sIt);
	std::vector<Term*> GetSubTerms() override;
	std::vector<char> GetSymbols();
	size_t GetNumberOfSubTerms() override;
	int Tree(StringTree& tree, int& maxDepth, bool withPtr=false) override;
	bool ReplaceSubTerm(Term* oldTerm, Term* newTerm) override;
	void InsertSubTerm(Term* relativeToTerm, Term* newTerm, int relativeIndex, char symbol=' ');
	bool RemoveSubTerm(Term* t) override;
	void AppendRight(Term* t, char symbol=' ');
	void AppendLeft(Term* t, char symbol=' ');
};
