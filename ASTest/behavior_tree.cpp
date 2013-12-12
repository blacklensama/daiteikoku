#include "behavior_tree.h"
#include "EnumUtil.h"

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

void BlackBoardForScript::Release()
{
	delete _instance;
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

void BevNode::addFunction(string name, string script, string funcName)
{

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

SequenceNode::~SequenceNode()
{
	cout << "SequenceNode" << endl;
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

SelectorNode::~SelectorNode()
{
	cout << "SelectorNode" << endl;
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

ParallelNode::~ParallelNode()
{
	cout << "ParallelNode" << endl;
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
	for (auto i : _ctxList)
	{
		i->Release();
	}
	cout << "delect action" << endl;
}

void ActionNode::addFunction(string name, string script, string funcName)
{
	ASEngine* as = ASEngine::Instance();
	asIScriptContext* ctx = as->getCtx();
	ctx->Prepare(as->CompileScript(name, script, _nodeName, funcName));
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

void ConditionNode::addFunction(string name, string script, string funcName)
{
	ASEngine* as = ASEngine::Instance();
	_ctx = as->getCtx();
	_ctx->Prepare(as->CompileScript(name, script, _nodeName, funcName));
}

ConditionNode::~ConditionNode()
{
	ASEngine* as = ASEngine::Instance();
	_ctx->Release();
	cout << "delect conditionNode" << endl;
}

DecoratorNode::DecoratorNode(string nodeName, RunStatus runStatus, BevNode* parents /* = NULL */):BevNode(nodeName, runStatus, parents)
{
	_nodeKind = Decortaor_Node;
	_ctx = NULL;
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

void DecoratorNode::addFunction(string name, string script, string funcName)
{
	if (script=="")
	{
		return;
	}
	ASEngine* as = ASEngine::Instance();
	_ctx = as->getCtx();
	_ctx->Prepare(as->CompileScript(name, script, _nodeName, funcName));
}

DecoratorNode::~DecoratorNode()
{
	cout << "DecoratorNode" << endl;
	ASEngine* as = ASEngine::Instance();
	if (_ctx != NULL)
	{
		_ctx->Release();
	}
}

BehaviorTreeObject::BehaviorTreeObject()
{
	head = NULL;
}

bool BehaviorTreeObject::Update()
{
	return head->Update();
}

BehaviorTreeObject::~BehaviorTreeObject()
{
	delete head;
}

BevNode* ILoadFromXml::loadFromXml(string path)
{
	xml_document doc;
	if (!doc.load_file(path.c_str()))
	{
		return NULL;
	}
	xml_node node = doc.child("newObj").child("Node");
	return loadFromNode(node);
}

BevNode* ILoadFromXml::loadFromNode(xml_node node, BevNode* parents/* =NULL */)
{
	BevNode* n = NULL;
	string nodeKind = node.attribute("nodeKind").as_string();
	string nodeName = node.attribute("nodeName").as_string();
	string runStatus = node.attribute("runStatus").as_string();
	NodeKind kind = (NodeKind)EnumUtil::getEnumValue(nodeKind);
	RunStatus status = (RunStatus)EnumUtil::getEnumValue(runStatus);
	string script = node.attribute("script").as_string();
	string funcName = node.attribute("scriptName").as_string();
	switch (kind)
	{
	case Action_Node:
		{
			n = new ActionNode(nodeName, status, parents);
			break;
		}
	case CompositeNode_ParallelNode:
		{
			n = new ParallelNode(nodeName, status, parents);
			break;
		}
	case CompositeNode_SelectorNode:
		{
			n = new SelectorNode(nodeName, status, parents);
			break;
		}
	case CompositeNode_SequenceNode:
		{
			n = new SequenceNode(nodeName, status, parents);
			break;
		}
	case Condition_Node:
		{
			n = new ConditionNode(nodeName, status, parents);
			break;
		}
	case Decortaor_Node:
		{
			n = new DecoratorNode(nodeName, status, parents);
			break;
		}
	default:
		break;
	}
	if (!n)
	{
		return n;
	}
	n->addFunction("main", script, funcName);
	for (auto i : node.children())
	{
		n->addChildren(loadFromNode(i, n));
	}
	return n;
}