#include "Connect2.h"

using namespace std;

Connect2::Connect2(Term* _parent)
: BinaryTerm(_parent)
{
	treeLabel = "co2";
}
string Connect2::Print()
{
	assert(sub1!=nullptr);
	assert(sub2!=nullptr);
	return sub1->Print() + sub2->Print();
}
string Connect2::Tex()
{
	assert(sub1!=nullptr);
	assert(sub2!=nullptr);
	return sub1->GetTex() + sub2->GetTex();
}
