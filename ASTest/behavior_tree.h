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
	void removeAllEvent();
	static void Release();
protected:
	BlackBoardForScript();
private:
	vector<systemEvent> _stList;
	static BlackBoardForScript* _instance;
};

class NodeMgr
{
public:
	static NodeMgr* Instance();
	void addNode(BevNode* node);
	void clearNode();
	void changeNodeStatic(string name, RunStatus statue);
	static void Release();
protected:
	NodeMgr();
	~NodeMgr();
private:
	static NodeMgr* _instance;
	multimap<string, BevNode*> _mgr;
};

class BevNode
{
public:
	BevNode(string nodeName, RunStatus runStatus, BevNode* parents = NULL);
	virtual bool Update(void* point) = 0;
	virtual BevNode* getParent();
	virtual vector<BevNode*> getChild();
	virtual string getName();
	virtual void setRunStatus(RunStatus rs);
	virtual RunStatus getRunStatus();
	virtual NodeKind getNodeKind();
	virtual void addFunction(string name, string script, string funcName);
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
	virtual bool Update(void* point);
	~SequenceNode();
protected:
private:
};

class SelectorNode:public BevNode
{
public:
	SelectorNode(string nodeName, RunStatus runStatus, BevNode* parents = NULL);
	virtual bool Update(void* point);
	~SelectorNode();
protected:
private:
};

class ParallelNode:public BevNode
{
public:
	ParallelNode(string nodeName, RunStatus runStatus, BevNode* parents = NULL);
	virtual bool Update(void* point);
	~ParallelNode();
protected:
private:
};

class ActionNode:public BevNode
{
public:
	ActionNode(string nodeName, RunStatus runStatus, BevNode* parents = NULL);
	virtual bool Update(void* point);
	~ActionNode();
	void addFunction(string name, string script, string funcName);
protected:
	vector<asIScriptContext*> _ctxList;
private:
};

class ConditionNode:public BevNode
{
public:
	ConditionNode(string nodeName, RunStatus runStatus, BevNode* parents = NULL);
	virtual bool Update(void* point);
	~ConditionNode();
	void addFunction(string name, string script, string funcName);
protected:
	asIScriptContext* _ctx;
private:
};

class DecoratorNode:public BevNode
{
public:
	DecoratorNode(string nodeName, RunStatus runStatus, BevNode* parents = NULL);
	virtual bool Update(void* point);
	virtual bool checkResult();
	void addFunction(string name, string script, string funcName);
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
	BehaviorTreeObject(string str);
	void reload(string path);
	bool Update(void* point = NULL);
	~BehaviorTreeObject();
protected:
private:
	BevNode* head;
};