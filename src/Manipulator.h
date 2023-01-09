/*!
 * @file DEQ.h
 * @brief Contains Main Function and Console Output commands
 *
 *  Created on: 2022-12-16
 *      Author: Moritz Geßner
 *
 * Whenever new Terms are created, they will either be embedded in the current
 * via a Manipulator::Replace() command or via a Append/Insert/... Command of
 * one of the other Terms. Thus for every critical case, where the rootTerm
 * of the tree might be changed, Replace() will handle the situation.
 *
 *
 *
 */

#pragma once

#include "TermsAutonomous/Cursor.h"
#include "TermsAutonomous/Empty.h"
#include "TermsAutonomous/Number.h"
#include "TermsAutonomous/Raw.h"
#include "TermsAutonomous/Variable.h"
#include "TermsSingular/Bracket.h"
//#include "TermsBinary/Connect2.h"
#include "TermsBinary/Power.h"
#include "TermsBinary/Subscript.h"
#include "TermsMultiple/Addition.h"
#include "TermsMultiple/Multiplication.h"
#include "TermsMultiple/Connection.h"
#include "Utility/FilePrinter.h"

class Manipulator
{
private:
	Term* rootTerm;
	void Replace(Term* oldTerm, Term* newTerm); // Sets new Parent of newTerm, and links this parent's subTerm to it, Deals with terms being rootTerm
	Term* GetRightmostTerm(Term* t);
	Term* GetLeftmostTerm(Term* t);
	void RemoveEmptyRaw(Raw* raw);
	void DeleteTerm(Term* t);
	void DeleteSubTerms(Term* t);
	template<typename T> void SplitMultiTerm(T* multi, Term* at, MultiTerm*& left, MultiTerm*& right);
	void SplitUntilAddition(Term* at, Term*& left, Term*& right, MultiTerm* add);
	void SplitUntilMultiplication(Term* at, Term*& left, Term*& right);
	void ReduceTerm(Term* t);

	static Term* rootTermParent;
public:
	std::string debugText = "";
	Manipulator();
	void SetrootTerm(Term*& _rootTerm);
	Term*& GetrootTerm();
	void InsertDigit(int digit);
	void InsertAddition(char sign);
	void Backspace(); // Backspace keyboard action
	void Del(); // Delete Keyboard action
	void CursorMoveRight();
	void CursorMoveLeft();
	int Latex(Term*& t);
	bool CheckTermLinks(Term*& t); // Returns 0 if everything is fine, 1 when errors are found
	Term* CursorLeft();
	Term* CursorRight();
};
