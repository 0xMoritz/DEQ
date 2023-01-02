/*!
 * @file Cursor.h
 * @brief Contains class for the cursor in interactive input of an equation
 *
 *  Created on: 2022-12-26
 *      Author: Moritz Geßner
 */

#pragma once

#include "../Term/AutonomousTerm.h"


class Cursor : public AutonomousTerm
{
private:
	static Cursor* activeCursor; // I suppose it might be usefull to have more than one cursor, to store in not actively editing equations for instance, but only one cursor should be capable of writing active input.
public:
	Cursor(Term* _parent);
	std::string Print() override;
	std::string Tex() override;

	static Cursor* GetActive();
	static void SetActive(Cursor* newActive);
};
