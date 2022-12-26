/*!
 * @file Connect2.h
 * @brief Contains class for undefined relation between two consecutive Terms
 *
 *  Created on: Dec 26, 2022
 *      Author: Moritz Geßner
 */

#pragma once

#include "../Term/BinaryTerm.h"


class Connect2 : public BinaryTerm
{
public:
	Connect2(Term* _parent);
	std::string Print() override;
	std::string Tex() override;
};
