/*!
 * @file Connect2.h
 * @brief Contains class for undefined relation between two consecutive Terms
 *
 *  Created on: 2022-12-26
 *      Author: Moritz Geßner
 */

#pragma once

#include "../Term/BinaryTerm.h"


class Connect2 : public BinaryTerm
{
public:
	Connect2(Term* _parent);
	std::string Tex() override;
	std::string Print() override;
};
