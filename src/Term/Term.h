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
	Term* parent = nullptr;
	std::string treeLabel = "err";
	std::string TreeLabel(bool withPtr);
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
	virtual int Tree(StringTree& tree, int& maxDepth, bool withPtr=false);
	int TreeWithAddress(StringTree& tree, int& maxDepth);
	virtual bool ReplaceSubTerm(Term* oldTerm, Term* newTerm); // Return 1 if Term was found and replaced, 0 if not
	virtual size_t GetNumberOfSubTerms();

	static std::string PtrAddress(Term* ptr);
	static Term* WithoutCursor(Term* t);

	template<typename T> static bool IsType(const Term* t)
	{
		// Comparing the pointers will always output typeid(t)=typeid(Term*), by dereferencing it we force the most derived type on t and can compare.
		if (t == nullptr)
			return 0;
		else
			return typeid(*t) == typeid(T);
		// This also works I think:
		//return (dynamic_cast<T*>(t) != nullptr);
	};
	template<typename T> static bool IsDerivedFrom(Term* t)
	{
		// Also returns true if t is exactly of type T
		if (t == nullptr)
			return 0;
		else
			return (dynamic_cast<T*>(t) != nullptr);
	};
	static bool AreTypesEqual(const Term* t1, const Term* t2)
	{
		if (t1 == nullptr || t2 == nullptr)
			return 0;
		else
			return typeid(*t1) == typeid(*t2);
	}
};
