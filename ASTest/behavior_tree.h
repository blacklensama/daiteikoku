#pragma once
#include "ASEngine.h"
#include "systemEvent.h"


enum RunStatus
{
	Completed,
	Failure,
	Running,
};

enum NodeKind
{
	CompositeNode_SelectorNode,
	CompositeNode_SequenceNode,
	CompositeNode_ParallelNode,
	Decortaor_Node,
	Condition_Node,
	Action_Node,
};

class BlackBoardForScript
{
public:
	static BlackBoardForScript* Instance();
	void addSystemEvent(systemEvent s);
	systemEvent getSystemEventByIndex(int num);
	void removeSystemEventByIndex(int num);
	int getListLength();
protected:
	BlackBoardForScript();
private:
	vector<systemEvent> _stList;
	static BlackBoardForScript* _instance;
};

class BevNode
{
public:
	BevNode(string nodeName, RunStatus runStatus, BevNode* parents = NULL);
	virtual bool Update() = 0;
	virtual BevNode* getParent();
	virtual vector<BevNode*> getChild();
	virtual string getName();
	virtual void setRunStatus(RunStatus rs);
	virtual RunStatus getRunStatus();
	virtual NodeKind getNodeKind();
	virtual void addChildren(BevNode* b);
	virtual ~BevNode();
protected:
	string _nodeName;
	NodeKind _nodeKind;
	RunStatus _runStatus;
	vector<BevNode*> _children;
	BevNode* _parents;
private:
};

class SequenceNode:BevNode
{
public:
	SequenceNode(string nodeName, RunStatus runStatus, BevNode* parents = NULL);
	virtual bool Update();
protected:
private:
};

class SelectorNode:BevNode
{
public:
	SelectorNode(string nodeName, RunStatus runStatus, BevNode* parents = NULL);
	virtual bool Update();
protected:
private:
};

class ParallelNode:BevNode
{
public:
	ParallelNode(string nodeName, RunStatus runStatus, BevNode* parents = NULL);
	virtual bool Update();
protected:
private:
};

class ActionNode:BevNode
{
public:
	ActionNode(string nodeName, RunStatus runStatus, BevNode* parents = NULL);
	virtual bool Update();
	virtual ~ActionNode();
	void addFunction(string name, string script);
protected:
	vector<asIScriptContext*> _ctxList;
private:
};

class ConditionNode:BevNode
{
public:
	ConditionNode(string nodeName, RunStatus runStatus, BevNode* parents = NULL);
	virtual bool Update();
	virtual ~ConditionNode();
	void addFunction(string name, string script);
protected:
	asIScriptContext* _ctx;
private:
};

class DecoratorNode:BevNode
{
public:
	DecoratorNode(string nodeName, RunStatus runStatus, BevNode* parents = NULL);
	virtual bool Update();
	virtual bool checkResult();
protected:
	vector<bool> _listResult;
private:
};