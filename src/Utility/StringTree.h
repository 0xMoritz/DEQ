/*!
 * @file StringTree.h
 * @brief Contains Library includes
 *
 *  Created on: Dec 19, 2022
 *      Author: Moritz Geßner
 */

#pragma once

#include "../Global.h"


class StringTree
{
public:
	std::list<StringTree*> subTrees;
	std::string s = "";
	std::string Write(int depth);
};
