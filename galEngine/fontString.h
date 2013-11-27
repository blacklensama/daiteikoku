#pragma once

#include "font.h"
#include "stdafx.h"

class StringFont : public xiayuObject
{
public:
	StringFont(wstring str);
	~StringFont(){}
	void draw();
	void draw(float y);
	void update();
	void init(wstring str);
	void init(xiayuWString& str);
	void all_to_black();
	inline galString getStatue()
	{
		return _flags;
	}
	inline void setStatus(galString f)
	{
		_flags = f;
	}
	wstring ToWString()
	{
		return _nowRead.ToWString();
	}
private:
	xiayuWString		_nowRead;
	galString			_flags;
	ALLEGRO_COLOR		_color;
	float				_y;
	vector<CharFont*>	_effect;
	int					_startnum;
	int					_starttime;
};