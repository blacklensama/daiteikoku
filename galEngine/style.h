#pragma once 

#include "stdafx.h"

class style : public xiayuObject
{
public:
	void draw(ALLEGRO_BITMAP* bitmap);
	void draw(ALLEGRO_BITMAP* bitmap, unsigned char alphe);
	void set_point(float x, float y);
	void update();
	void parse(xiayuWString);
protected:
private:
	ALLEGRO_COLOR _color;
	xiayuInt _time;
	float _x;
	float _y;
	float _ex;
	float _ey;
	float _vx;
	float _vy;
	xiayuWString _style;
};