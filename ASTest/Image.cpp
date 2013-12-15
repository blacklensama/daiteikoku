#include "Image.h"
#include "ImageManager.h"

ImageInfo::ImageInfo()
{
	w = h = 0;
}

ImageInfo::ImageInfo(ALLEGRO_BITMAP* bitmap)
{
	w = al_get_bitmap_width(bitmap);
	h = al_get_bitmap_height(bitmap);
}

Point ImageInfo::operator ()()
{
	return Point(w/2, h/2);
}

Image::Image(ALLEGRO_BITMAP* bitmap, Point p /* = Point */)
{
	_bitmap = bitmap;
	_p = p;
	_info = ImageInfo(_bitmap);
}

Image::Image(string name, Point p /* = Point */)
{
	ImageManager* mgr = ImageManager::Instance();
	_bitmap = mgr->getBitmap(name);
	_p = p;
	_info = ImageInfo(_bitmap);
}

Point Image::getDrawPoint()
{
	return _p - _info();
}

Point Image::getPoint()
{
	return _p;
}

void DrawImage(Image* i)
{
	Point p = i->getPoint();
	al_draw_bitmap(i->getBitmap(), p.x, p.y, 0);
}

void DrawImage(Image* i, float c)
{
	Point p = i->getPoint();
	al_draw_tinted_bitmap(i->getBitmap(), al_map_rgba_f(c, c, c ,c), p.x, p.y, 0);
}

void DrawImage(Image* i, Point p)
{
	p = i->getPoint() - p;
	al_draw_bitmap(i->getBitmap(), p.x, p.y , 0);
}

void DrawImage(Image* i, Point p, float c)
{
	p = i->getPoint() - p;
	al_draw_tinted_bitmap(i->getBitmap(),al_map_rgba_f(c, c, c ,c), p.x, p.y, 0);
}