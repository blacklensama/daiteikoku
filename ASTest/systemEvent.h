#pragma once
#include "stdafx.h"

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

struct Point
{
	Point();
	Point(float v);
	Point(float x1, float y1);
	Point(const Point& p);
	Point& operator=(const Point& p);
	//EnumTriggerType operator-(Point& p);
	Point& operator-(const Point& p);
	Point& operator+(const Point& p);
	bool operator==(const Point& p);
	bool IsInRange(Point& p1, Point& p2);
	float x;
	float y;
};

class systemEvent
{
public:
	systemEvent();
	void Addref();
	void Release();
	bool operator==(systemEvent s);
	EnumTriggerType e;
	Point p;
	int key;
protected:
	int refCount;
};

systemEvent* systemEvent_Factory();