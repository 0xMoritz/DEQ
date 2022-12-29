#include "StringTree.h"

using namespace std;

StringTree::~StringTree()
{
	for (list<StringTree*>::iterator subTree = subTrees.begin(); subTree != subTrees.end(); subTree++)
	{
		delete *subTree;
	}
}

string StringTree::Write(int depth)
{
	// Reorganize StringTree in layers
	list<StringTree*>* layers[depth];
	list<StringTree*> emptyStringTrees = list<StringTree*>{}; // Collect empty Stringtrees
	layers[0] = new list<StringTree*>{this};
	for (int i=1; i<depth; i++)
	{
		layers[i] = new list<StringTree*>{};
		for (list<StringTree*>::iterator tree = layers[i-1]->begin(); tree != layers[i-1]->end(); tree++)
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
			for (list<StringTree*>::iterator subTree = (**tree).subTrees.begin(); subTree != (**tree).subTrees.end(); subTree++)
			{
				layers[i]->push_back(*subTree);
			}
		}
	}

	// Print
	string out = "";
	for (int i=0; i<depth; i++)
	{
		for (list<StringTree*>::iterator tree = layers[i]->begin(); tree != layers[i]->end(); tree++)
		{
			out += (**tree).s;
		}
		out += "\n";
	}
	// delete Layer lists
	for (int i=0; i<depth; i++)
	{
		delete layers[i];
	}
	// delete Empty StringTrees
	for (list<StringTree*>::iterator empty = emptyStringTrees.begin(); empty != emptyStringTrees.end(); empty++)
	{
		delete *empty;
	}
	return out;
}
