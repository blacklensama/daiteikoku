#include "behavior_tree.h"

BevNode::BevNode(string nodeName, RunStatus runStatus, BevNode* parents)
{
	_nodeName = nodeName;
	_runStatus = runStatus;
	_parents = parents;
}

void BevNode::addChildren(BevNode* b)
{
	_children.push_back(b);
}

void BevNode::setRunStatus(RunStatus rs)
{
	_runStatus = rs;
}

RunStatus BevNode::getRunStatus()
{
	return _runStatus;
}

NodeKind BevNode::getNodeKind()
{
	return _nodeKind;
}

BevNode* BevNode::getParent()
{
	return _parents;
}

vector<BevNode*> BevNode::getChild()
{
	return _children;
}

string BevNode::getName()
{
	return _nodeName;
}

BevNode::~BevNode()
{
	for (auto i : _children)
	{
		delete i;
	}
}

SequenceNode::SequenceNode(string nodeName, RunStatus runStatus, BevNode* parents /* = NULL */):BevNode(nodeName, runStatus, parents)
{
	_nodeKind = CompositeNode_SequenceNode;
}

bool SequenceNode::Update()
{
	if (_runStatus == Running)
	{
		for (auto i : _children)
		{
			if (!i->Update())
			{
				return false;
			}
		}
		return true;
	}else if (_runStatus == Failure)
	{
		return false;
	}else if (_runStatus == Completed)
	{
		return true;
	}
}

SelectorNode::SelectorNode(string nodeName, RunStatus runStatus, BevNode* parents /* = NULL */):BevNode(nodeName, runStatus, parents)
{
	_nodeKind = CompositeNode_SelectorNode;
}

bool SelectorNode::Update()
{
	if (_runStatus == Running)
	{
		for (auto i : _children)
		{
			if (i->Update())
			{
				return true;
			}
		}
		return false;
	}else if (_runStatus == Failure)
	{
		return false;
	}else if (_runStatus == Completed)
	{
		return true;
	}
}

ParallelNode::ParallelNode(string nodeName, RunStatus runStatus, BevNode* parents /* = NULL */):BevNode(nodeName, runStatus, parents)
{
	_nodeKind = CompositeNode_ParallelNode;
}

bool ParallelNode::Update()
{
	if (_runStatus == Running)
	{
		bool flag = false;
		for (auto i:_children)
		{
			if (i->Update())
			{
				flag = true;
			}
		}
		if (flag)
		{
			return true;
		}else 
		{
			return false;
		}
	}else if (_runStatus == Failure)
	{
		return false;
	}else if (_runStatus == Completed)
	{
		return true;
	}
}

ActionNode::ActionNode(string nodeName, RunStatus runStatus, BevNode* parents /* = NULL */):BevNode(nodeName, runStatus, parents)
{
	_nodeKind = Action_Node;
}

bool ActionNode::Update()
{
	if (_runStatus == Running)
	{
		for (auto i : _ctxList)
		{
			i->Execute();
		}
		return true;
	}else if (_runStatus == Failure)
	{
		return false;
	}else if (_runStatus == Completed)
	{
		return true;
	}
}

ActionNode::~ActionNode()
{
	for (auto i : _ctxList)
	{
		i->Release();
	}
}

void ActionNode::addFunction(string name, string script)
{
	ASEngine* as = ASEngine::Instance();
	asIScriptContext* ctx = as->getCtx();
	ctx->Prepare(as->CompileScript(name, script, name, _nodeName));
	_ctxList.push_back(ctx);
}