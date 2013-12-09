#include "behavior_tree.h"

BlackBoardForScript* BlackBoardForScript::_instance = NULL;

BlackBoardForScript* BlackBoardForScript::Instance()
{
	if (_instance == NULL)
	{
		_instance = new BlackBoardForScript();
	}
	return _instance;
}

BlackBoardForScript::BlackBoardForScript()
{

}

int BlackBoardForScript::getListLength()
{
	return _stList.size();
}

void BlackBoardForScript::addSystemEvent(systemEvent s)
{
	_stList.push_back(s);
}

systemEvent BlackBoardForScript::getSystemEventByIndex(int num)
{
	return _stList[num];
}

void BlackBoardForScript::removeSystemEventByIndex(int num)
{
	_stList.erase(_stList.begin() + num);
}

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
	ASEngine* as = ASEngine::Instance();
	as->ReleaseMode(_nodeName);
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

ConditionNode::ConditionNode(string nodeName, RunStatus runStatus, BevNode* parents /* = NULL */):BevNode(nodeName, runStatus, parents)
{
	_nodeKind = Condition_Node;
}

bool ConditionNode::Update()
{
	if (_runStatus == Running)
	{
		BlackBoardForScript* bb = BlackBoardForScript::Instance();
		_ctx->SetArgObject(0, bb);
		_ctx->Execute();
		return _ctx->GetReturnQWord()==1;
	}else if (_runStatus == Failure)
	{
		return false;
	}else if (_runStatus == Completed)
	{
		return true;
	}
}

void ConditionNode::addFunction(string name, string script)
{
	ASEngine* as = ASEngine::Instance();
	_ctx = as->getCtx();
	_ctx->Prepare(as->CompileScript(name, script, name, _nodeName));
}

ConditionNode::~ConditionNode()
{
	ASEngine* as = ASEngine::Instance();
	as->ReleaseMode(_nodeName);
	_ctx->Release();
}

DecoratorNode::DecoratorNode(string nodeName, RunStatus runStatus, BevNode* parents /* = NULL */):BevNode(nodeName, runStatus, parents)
{
	_nodeKind = Decortaor_Node;
}

bool DecoratorNode::Update()
{
	if (_runStatus == Running)
	{
		for (auto i:_children)
		{
			_listResult.push_back(i->Update());
		}
	}else if (_runStatus == Failure)
	{
		return false;
	}else if (_runStatus == Completed)
	{
		return true;
	}
	return checkResult();
}

bool DecoratorNode::checkResult()
{
	for (auto i : _listResult)
	{
		if (!i)
		{
			return false;
		}
	}
	return true;
}