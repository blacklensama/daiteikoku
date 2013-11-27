#pragma once
#include "stdafx.h"
class fps :
	public xiayuObject
{
public:
	fps(void);
	void updata();
	void draw();
	xiayuDouble getFps()
	{
		return _fps;
	}
	~fps(void);
private:
	xiayuDouble		_fps;
	xiayuDouble		_lastsecond; 
	xiayuInt		_frames_accum;
	xiayuFloat		_x;
	xiayuFloat		_y;
	ALLEGRO_FONT*	_myFont;
};

