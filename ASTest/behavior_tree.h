#pragma once
#include <iostream>
#include <vector>

using namespace std;

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
	DecortaorNode,
	ConditionNode,
	ActionNode,
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