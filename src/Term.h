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


class SingularTerm : public Term
{
protected:
	Term* sub = nullptr;
public:
	SingularTerm(Term* _parent);
};


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


class MultiTerm : public Term
{
protected:
	std::list<Term*>* subTerms;
public:
	MultiTerm(Term* _parent);
	int Tree(StringTree& tree, int& maxDepth) override;
};
