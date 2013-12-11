#include "EnumUtil.h"
#include "behavior_tree.h"
#define REGISTERENUM(x) RegisterEnumValue(#x, x)
map<string,int> EnumUtil::EnumReflection = map<string, int>();

void EnumUtil::RegisterEnumValue(string str, int num)
{
	EnumReflection.insert(make_pair(str, num));
}

int EnumUtil::getEnumValue(string str)
{
	return EnumReflection[str];
}

void EnumUtil::init()
{
	REGISTERENUM(CompositeNode_SelectorNode);
	REGISTERENUM(CompositeNode_ParallelNode);
	REGISTERENUM(CompositeNode_SequenceNode);
	REGISTERENUM(Decortaor_Node);
	REGISTERENUM(Condition_Node);
	REGISTERENUM(Action_Node);
	REGISTERENUM(Running);
	REGISTERENUM(Completed);
	REGISTERENUM(Failure);
}