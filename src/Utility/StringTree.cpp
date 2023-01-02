#include "StringTree.h"

using namespace std;
using ITERATOR = vector<StringTree*>::iterator;

StringTree::~StringTree()
{
	for (ITERATOR subTree = subTrees.begin(); subTree != subTrees.end(); subTree++)
	{
		delete *subTree;
	}
}

string StringTree::Write(int depth)
{
	// Reorganize StringTree in layers
	vector<StringTree*>* layers[depth];
	vector<StringTree*> emptyStringTrees = vector<StringTree*>{}; // Collect empty Stringtrees
	layers[0] = new vector<StringTree*>{this};
	for (int i=1; i<depth; i++)
	{
		layers[i] = new vector<StringTree*>{};
		for (ITERATOR tree = layers[i-1]->begin(); tree != layers[i-1]->end(); tree++)
		{
			// Normalize, such that all the parts have the same depth, i.e. if there are no subtrees,
			// add an empty element that contains an empty string to sustain width of output.
			if ((**tree).subTrees.size() == 0)
			{
				StringTree* empty = new StringTree;
				emptyStringTrees.push_back(empty);
				empty->s = string((**tree).s.length(), ' ');
				layers[i]->push_back(empty);
			}
			for (ITERATOR subTree = (**tree).subTrees.begin(); subTree != (**tree).subTrees.end(); subTree++)
			{
				layers[i]->push_back(*subTree);
			}
		}
	}

	// Print
	string out = "";
	for (int i=0; i<depth; i++)
	{
		for (ITERATOR tree = layers[i]->begin(); tree != layers[i]->end(); tree++)
		{
			out += (**tree).s;
		}
		out += "\n";
	}
	// delete Layer vectors
	for (int i=0; i<depth; i++)
	{
		delete layers[i];
	}
	// delete Empty StringTrees
	for (ITERATOR empty = emptyStringTrees.begin(); empty != emptyStringTrees.end(); empty++)
	{
		delete *empty;
	}
	return out;
}
