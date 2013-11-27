#pragma once

#include "stdafx.h"
#include "systemEvent.h"

class rectangle : public xiayuObject
{
public:
	rectangle();
	rectangle(float x1, float y1, float x2, float y2);
	rectangle(Point p1, Point p2);
	void setRect(float x1, float y1, float x2, float y2);
	bool InRectangle(float x1, float x2);
	bool InRectangle(Point p);
	bool InRectangle(rectangle r);
	float _x1,_x2,_y1,_y2;
	~rectangle(){};
private:
};