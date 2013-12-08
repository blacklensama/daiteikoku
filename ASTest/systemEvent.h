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
	Point(float x1, float y1);
	EnumTriggerType operator-(Point p);
	bool operator==(Point p);
	float x;
	float y;
};

struct systemEvent
{
	systemEvent();
	bool operator==(systemEvent s);
	EnumTriggerType e;
	Point p;
	int key;
};