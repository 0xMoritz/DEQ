/*!
 * @file SingularTerm.h
 * @brief Subclass of Term with one subTerm
 *
 *  Created on: Dec 26, 2022
 *      Author: Moritz Geßner
 */

#pragma once

#include "Term.h"


class SingularTerm : public Term
{
protected:
	Term* sub = nullptr;
public:
	SingularTerm(Term* _parent);
};
