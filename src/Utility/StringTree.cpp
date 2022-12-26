#include "StringTree.h"

using namespace std;

string StringTree::Write(int depth)
{
	// Reorganize StringTree in layers
	list<StringTree*>* layers[depth];
	layers[0] = new list<StringTree*>{this};
	for (int i=1; i<depth; i++)
	{
		layers[i] = new list<StringTree*>{};
		for (auto tree = layers[i-1]->begin(); tree != layers[i-1]->end(); tree++)
		{
			// Normalize, such that all the parts have the same depth, i.e. if there are no subtrees,
			// add an empty element that contains an empty string to sustain width of output.
			if ((**tree).subTrees.size() == 0)
			{
				StringTree* empty = new StringTree;
				empty->s = string((**tree).s.length(), ' ');
				layers[i]->push_back(empty);
			}
			for (auto subTree = (**tree).subTrees.begin(); subTree != (**tree).subTrees.end(); subTree++)
			{
				layers[i]->push_back(*subTree);
			}
		}
	}

	// Print
	string out = "";
	for (int i=0; i<depth; i++)
	{
		for (auto tree = layers[i]->begin(); tree != layers[i]->end(); tree++)
		{
			out += (**tree).s;
		}
		out += "\n";
	}
	return out;
}
