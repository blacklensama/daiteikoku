#pragma once
#include "stdafx.h"
#include "sysConfig.h"
class CharFont : public xiayuObject
{
public:
	CharFont()
	{
		_value = L" ";
		al_color_to_white(&_color);
	}
	CharFont(xiayuWChar c)
	{
		_value = c;
		al_color_to_white(&_color);
	}
	void init(xiayuWChar c)
	{
		_value = c;
	}
	void setPoint(float x, float y)
	{
		_x = x;
		_y = y;
	}
	xiayuWString getValue()
	{
		return _value;
	}
	void ToBlack()
	{
		al_color_to_black(&_color);
	}
	~CharFont()
	{

	}
	inline void draw()
	{
		al_draw_text(_font, _color, _x, _y, 0, _value.ToWString().c_str());
	}
	inline void draw(float y)
	{
		al_draw_text(_font, _color, _x, _y + y, 0, _value.ToWString().c_str());
	}
	inline void updata()
	{
		al_add_color(&_color, 0.01);
	}
	inline static void loadFont()
	{
		if (_font == NULL)
		{
			_font = al_load_font("MSYH.TTF", 20, 0);
		}
		if (_font == NULL)
		{
			cout << "can't load the font" << endl;
		}
	}
	inline static ALLEGRO_FONT* getFont()
	{
		if (_font == NULL)
		{
			cout << "can't load the font" << endl;
		}
		return _font;
	}
private:
	xiayuWString			_value;
	ALLEGRO_COLOR			_color;
	float					_x,_y;
	static ALLEGRO_FONT*	_font;
};