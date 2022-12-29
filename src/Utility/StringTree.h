/*!
 * @file StringTree.h
 * @brief Contains Library includes
 *
 *  Created on: 2022-12-19
 *      Author: Moritz Geßner
 */

#pragma once

#include "../Global.h"
#include "Utility.h"


class StringTree
{
public:
	~StringTree();
	std::list<StringTree*> subTrees;
	std::string s = "";
	std::string Write(int depth);
};
