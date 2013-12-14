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