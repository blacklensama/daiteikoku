#include "font.h"

font* font::_instance = NULL;

font* font::Instance()
{
	if (_instance == NULL)
	{
		_instance = new font();
	}
	return _instance;
}

ALLEGRO_FONT* font::getFont()
{
	return _font;
}

void font::Release()
{
	delete _instance;
}

font::font()
{
	_font = al_load_ttf_font("MSYH.TTF", 15, 0);assert(_font);
}

font::~font()
{
	al_destroy_font(_font);
}

void font::changeFontSize(int size)
{
	al_destroy_font(_font);
	_font = al_load_ttf_font("MSYH.TTF", size, 0);assert(_font);
}