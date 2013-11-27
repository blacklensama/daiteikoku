#include "style.h"

void style::draw(ALLEGRO_BITMAP* bitmap)
{
	al_draw_tinted_bitmap(bitmap, _color, _x, _y, 0);
}

void style::draw(ALLEGRO_BITMAP* bitmap, unsigned char alphe)
{
	al_draw_tinted_bitmap(bitmap, al_map_rgba(alphe, alphe, alphe, alphe), _x, _y, 0);
}

void style::update()
{

}

void style::parse(xiayuWString str)
{

}

void style::set_point(float x, float y)
{
	_x = x;
	_y = y;
}