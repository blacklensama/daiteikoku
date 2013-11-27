#pragma once

#include "stdafx.h"
#include "UIBase.h"

struct UIBaseCompare
{
	bool operator()(UIBase* u1, UIBase* u2)
	{
		return (u1->getPriority() < u2->getPriority());
	}
};

class UIManager
{
public:
	static UIManager* Instance();
	void init(string filePath);
	void RegisterUI(UIBase* b);
	void RemoveUI(string name);
	UIBase* getUIByName(string name);
	void draw();
	void clearUI();
	void update(systemEvent* s);
	bool setUIContent(UIBase* ui);//用于处理可以拖拽的控件，控件可以附加在别的控件上
protected:
	UIManager(){}
private:
	static UIManager* _instance;
	map<string,UIBase*> _ui;
	multiset<UIBase*, UIBaseCompare> _uiIndex;
};