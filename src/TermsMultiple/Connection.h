/*!
 * @file Connection.h
 * @brief Contains class for blank connection (i.e. without explicit symbol) of elements, replacement of Connect2, parses to multiplication after removal of cursor
 *
 *  Created on: 2023-01-04
 *      Author: Moritz Geßner
 */

#pragma once

#include "../Term/MultiTerm.h"
#include "../TermsAutonomous/Raw.h"


class Connection : public MultiTerm
{
public:
	Connection(Term* _parent);
	std::string Tex() override;
	void AppendRight(Term* t);
	std::string Print() override;
	void InsertSubTerm(Term* relativeToTerm, Term* newTerm, int relativeIndex);
	void RemoveSubTerm(Term* thisOne);
};
