/*!
 * @file Cursor.h
 * @brief Contains class for the cursor in interactive input of an equation
 *
 *  Created on: Dec 26, 2022
 *      Author: Moritz Geßner
 */

#pragma once

#include "../Term/AutonomousTerm.h"


class Cursor : public AutonomousTerm
{
private:
	Term* left;
	Term* right;
	static Cursor* activeCursor; // I suppose it might be usefull to have more than one cursor, to store in not actively editing equations for instance, but only one cursor should be capable of writing active input.
public:
	Cursor(Term* _parent);
	std::string Print() override;
	std::string Tex() override;
	Term* GetLeft();
	void SetLeft(Term* newLeft);
	Term* GetRight();
	void SetRight(Term* newRight);

	static Cursor* GetActive();
	static void SetActive(Cursor* newActive);
};
