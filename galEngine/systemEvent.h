#pragma once

#include "stdafx.h"

struct UIMessage
{
	int color;
	int time;
};

enum EnumTriggerType
{
	kTrig_None,
	kTrig_LeftClickUp,
	kTrig_RightClickUp,
	kTrig_KeyBroadUp,
	KTrig_KeyBroadDown,
	kTrig_LiftMouseMove,
	kTrig_LeftClickDown,
	kTrig_RightClickDown,
	kTrig_Left,
	kTrig_Right,
	kTrig_Up,
	kTrig_Down,
	kTrig_RightMouseMove
};

enum EnumGameStatue
{
	kTrig_PlayMovie,
	kTrig_PlayGalGame,
	kTrig_AutoPlayGalGame,
	kTrig_PlayActive,
	kTrig_Menu
};

struct Point
{
	Point(){}
	Point(float x1, float y1)
	{
		x = x1;
		y = y1;
	}
	EnumTriggerType operator-(Point p)
	{
		float dx = p.x - x;
		float dy = p.y - y;
		float d;
		if (dx == 0)
		{
			if (dy > 0)
			{
				return kTrig_Down;
			}else
				return kTrig_Up;
		}
		d = dy/dx;
		if (d > 0 && d < 1)
		{
			if (dy > 0)
			{
				return kTrig_Left;
			}else
				return kTrig_Right;
		}else if (d > 1)
		{
			if (dy > 0)
			{
				return kTrig_Up;
			}else
				return kTrig_Down;
		}else if (d < -1)
		{
			if (dy > 0)
			{
				return kTrig_Up;
			}else
				return kTrig_Down;
		}else if (d > -1 && d < 0)
		{
			if (dy > 0)
			{
				return kTrig_Right;
			}else
				return kTrig_Left;
		}
		return kTrig_None;
	}
	bool operator==(Point p)
	{
		if (p.x == x && p.y == y)
		{
			return true;
		}
		return false;
	}
	int x;
	int y;
};

struct systemEvent
{
	systemEvent()
	{
		remove = false;
	}
	bool operator==(systemEvent s)
	{
		if(s.e == e && s.p == p)
			return true;
		return false;
	}
	EnumTriggerType e;
	Point p;
	int key;
	bool remove;
};

class globalFunction
{
public:
	void init(string path="system\\globalFunction.xml");
	void addFunction(string& name, string& funcname, string& script);
	void update(systemEvent* s);
protected:
private:
	map<string, string> bind;
	map<string, asIScriptFunction*> function;
};

class SystemEventManager
{
public:
	static SystemEventManager* Instance()
	{
		if (_instance == NULL)
		{
			_instance = new SystemEventManager();
		}
		return _instance;
	}
	int RegisterTrigger(systemEvent* e)
	{
		switch (e->e)
		{
		case kTrig_LeftClickDown:
			{
				p = e->p;
				move = true;
				moveKind = kTrig_LeftClickDown;
				moveTime = 0;
			}
			break;
		case kTrig_RightClickDown:
			{
				p = e->p;
				move = true;
				moveKind = kTrig_RightClickDown;
				moveTime = 0;
			}
			break;
		case kTrig_LeftClickUp:
			{
				move = false;
				if (moveTime > 30)
				{
					systemEvent* se = new systemEvent();
					se->e = kTrig_LiftMouseMove;
					se->key = e->p - p;
					cout << se->key << endl;
					s.insert(make_pair(se->e, se));
				}
				auto i = s.lower_bound(e->e);
				auto j = s.upper_bound(e->e);
				if (i != j)
				{
					delete i->second;
					s.erase(i);
				}
			}
			break;
		case kTrig_RightClickUp:
			{
				move = false;
				if (moveTime > 30)
				{
					systemEvent* se = new systemEvent();
					se->e = kTrig_RightMouseMove;
					se->key = e->p - p;
					cout << se->key << endl;
					s.insert(make_pair(se->e, se));
				}
				auto i = s.lower_bound(e->e);
				auto j = s.upper_bound(e->e);
				if (i != j)
				{
					delete i->second;
					s.erase(i);
				}
			}
			break;
		case kTrig_KeyBroadUp:
			{
				for (auto i = s.lower_bound(KTrig_KeyBroadDown); i != s.upper_bound(KTrig_KeyBroadDown); i++)
				{
					if (e->key == (*i).second->key)
					{
						RemoveTrigger((*i).second);
						break;
					}
				}
			}
			break;
		default:
			break;
		}
		s.insert(make_pair(e->e, e));
		return e->e;
	}
	void RemoveTrigger(systemEvent* e)
	{
		for (auto i = s.begin(); i != s.end();)
		{
			if (i->second == e)
			{
				i = s.erase(i);
			}else
			{
				i++;
			}
		}
	}
	void RemoveAllTrigger()
	{
		for (auto i = s.begin(); i != s.end();)
		{
			if (i->second->e != KTrig_KeyBroadDown)
			{
				delete i->second;
				i = s.erase(i);
			}else
			{
				i++;
			}
		}
	}
	void Update();
	void setStatue(EnumGameStatue e);
protected:
	SystemEventManager()
	{
		statue = kTrig_Menu;
		move = 0;
		gf = new globalFunction();
		gf->init();
	}
private:
	void GFUpdate();
	void UIUpdate();
	void GameUpdate();
	multimap<EnumTriggerType, systemEvent*, greater<EnumTriggerType>> s;
	globalFunction* gf;
	static SystemEventManager* _instance;
	Point p;
	int moveTime;
	int moveKind;
	bool move;
	EnumGameStatue statue;
};

