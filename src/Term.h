/*!
 * @file Term.h
 * @brief Basis Class and Derived Classes of Graphalgorithm approach to Mathematical Fomulae
 *
 *  Created on: Dec 19, 2022
 *      Author: Moritz Geßner
 */

#pragma once

#include "StringTree.h"


class Term
{
protected:
	std::string treeLabel = "err";
public:
	//~Term() = default;
	virtual Term Derivative();
	virtual std::string Print();
	virtual std::string Tex();
	virtual int Tree(StringTree& tree, int& maxDepth);
};


class SingularTerm : public Term
{
protected:
	Term* sub = nullptr;
};


class BinaryTerm : public Term
{
protected:
	Term* sub1;
	Term* sub2;
public:
	BinaryTerm(Term* _sub1, Term* _sub2);
	int Tree(StringTree& tree, int& maxDepth) override;
};


class MultiTerm : public Term
{
protected:
	std::list<Term*>* subTerms;
public:
	int Tree(StringTree& tree, int& maxDepth) override;
};
