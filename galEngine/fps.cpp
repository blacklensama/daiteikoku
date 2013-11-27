#include "fps.h"
#include "font.h"


fps::fps(void):_lastsecond(0),_frames_accum(0),_x(580),_y(0)
{
	_myFont = CharFont::getFont();
}

void fps::updata()
{
	xiayuDouble t = al_get_time();
	if (t >= _lastsecond + 1) 
	{
		_fps = _frames_accum / (t - _lastsecond);
		_frames_accum = 0;
		_lastsecond = t;
	}	
	_frames_accum++;
}

void fps::draw()
{
	al_draw_text(_myFont, al_map_rgb(255, 255, 255), _x, _y, 0, _fps.ToString().c_str());
}

fps::~fps(void)
{
}
