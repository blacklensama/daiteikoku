#include "rectangle.h"

rectangle::rectangle()
{
	_x1 = _x2 = _y1 = _y2 = 0;
}

rectangle::rectangle(float x1, float y1, float x2, float y2)
{
	setRect(x1,y1,x2,y2);
}

rectangle::rectangle(Point p1, Point p2)
{
	setRect(p1.x, p1.y, p2.x, p2.y);
}

void rectangle::setRect(float x1, float y1, float x2, float y2)
{
	_x1 = x1;
	_x2 = x2;
	_y1 = y1;
	_y2 = y2;
}

bool rectangle::InRectangle(Point p)
{
	return InRectangle(p.x, p.y);
}

bool rectangle::InRectangle(float x1, float y1)
{
	if (x1 <= _x2 && x1 >= _x1)
	{
		if (y1 <= _y2 && y1 >= _y1)
		{
			return true;
		}
	}
	return false;
}

bool rectangle::InRectangle(rectangle r)
{
	Point p1(r._x1, r._y1);
	Point p2(r._x1, r._y2);
	Point p3(r._x2, r._y1);
	Point p4(r._x2, r._y2);
	if (InRectangle(p1)||InRectangle(p2)||InRectangle(p3)||InRectangle(p4))
	{
		return true;
	}else
		return false;
}