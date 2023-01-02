/*!
 * @file DEQ.h
 * @brief Contains Main Function and Console Output commands
 *
 *  Created on: 2022-12-16
 *      Author: Moritz Geßner
 */

#pragma once

#include "TermsAutonomous/Cursor.h"
#include "TermsAutonomous/Empty.h"
#include "TermsAutonomous/Number.h"
#include "TermsAutonomous/Raw.h"
#include "TermsAutonomous/Variable.h"
#include "TermsSingular/Bracket.h"
#include "TermsBinary/Connect2.h"
#include "TermsBinary/Power.h"
#include "TermsBinary/Subscript.h"
#include "TermsMultiple/Addition.h"
#include "TermsMultiple/Multiplication.h"
#include "Utility/FilePrinter.h"

class Manipulator
{
private:
	Term* root;
	void Replace(Term* oldTerm, Term* newTerm); // Sets new Parent of newTerm, and links this parent's subTerm to it, Deals with terms being root
	void FindCursorNeighbours(); // Finds and sets Cursor.left and Cursor.right
	Term* GetRightmostTerm(Term* t);
	Term* GetLeftmostTerm(Term* t);
	void DeleteTerm(Term* t);
	void DeleteSubTerms(Term* t);
public:
	std::string debugText = "";
	Manipulator();
	void SetRoot(Term*& _root);
	Term*& GetRoot();
	void InsertDigit(int digit);
	void Backspace();
	void Delete();
	void CursorMoveRight();
	void CursorMoveLeft();
	int Latex(Term*& t);
	bool CheckConnections(Term*& t);
};
