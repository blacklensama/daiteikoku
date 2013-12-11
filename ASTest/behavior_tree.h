#pragma once
#include "ASEngine.h"
#include "systemEvent.h"


class BevNode;

class ILoadFromXml
{
public:
	virtual BevNode* loadFromXml(string path);
	virtual BevNode* loadFromNode(xml_node node, BevNode* parents=NULL);
protected:
private:
};

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
	static void Release();
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
	virtual void addFunction(string name, string script);
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

class SequenceNode:public BevNode
{
public:
	SequenceNode(string nodeName, RunStatus runStatus, BevNode* parents = NULL);
	virtual bool Update();
	~SequenceNode();
protected:
private:
};

class SelectorNode:public BevNode
{
public:
	SelectorNode(string nodeName, RunStatus runStatus, BevNode* parents = NULL);
	virtual bool Update();
	~SelectorNode();
protected:
private:
};

class ParallelNode:public BevNode
{
public:
	ParallelNode(string nodeName, RunStatus runStatus, BevNode* parents = NULL);
	virtual bool Update();
	~ParallelNode();
protected:
private:
};

class ActionNode:public BevNode
{
public:
	ActionNode(string nodeName, RunStatus runStatus, BevNode* parents = NULL);
	virtual bool Update();
	~ActionNode();
	void addFunction(string name, string script);
protected:
	vector<asIScriptContext*> _ctxList;
private:
};

class ConditionNode:public BevNode
{
public:
	ConditionNode(string nodeName, RunStatus runStatus, BevNode* parents = NULL);
	virtual bool Update();
	~ConditionNode();
	void addFunction(string name, string script);
protected:
	asIScriptContext* _ctx;
private:
};

class DecoratorNode:public BevNode
{
public:
	DecoratorNode(string nodeName, RunStatus runStatus, BevNode* parents = NULL);
	virtual bool Update();
	virtual bool checkResult();
	void addFunction(string name, string script);
	~DecoratorNode();
protected:
	vector<bool> _listResult;
	asIScriptContext* _ctx;
private:
};

class BehaviorTreeObject:public ILoadFromXml
{
public:
	BehaviorTreeObject();
	bool Update();
	~BehaviorTreeObject();
protected:
private:
	BevNode* head;
};