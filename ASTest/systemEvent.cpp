#include "systemEvent.h"

Point::Point()
{
	x = y = 0;
}

Point::Point(float x1, float y1)
{
	x = x1;
	y = y1;
}

EnumTriggerType Point::operator-(Point p)
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

bool Point::operator==(Point p)
{
	if (p.x == x && p.y == y)
	{
		return true;
	}
	return false;
}

systemEvent::systemEvent()
{
	e = kTrig_None;
}

bool systemEvent::operator==(systemEvent s)
{
	if(s.e == e && s.p == p)
		return true;
	return false;
}