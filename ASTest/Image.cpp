#include "Image.h"
#include "ImageManager.h"

ImageInfo::ImageInfo()
{
	w = h = 0;
}

ImageInfo::ImageInfo(ALLEGRO_BITMAP* bitmap)
{
	if (bitmap)
	{
		w = al_get_bitmap_width(bitmap);
		h = al_get_bitmap_height(bitmap);
	}else
	{
		w = h = 0;
	}
}

Point ImageInfo::operator ()()
{
	return Point(w/2, h/2);
}

Image::Image()
{
	_bitmap = NULL;
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

Image::Image(xml_node& node)
{
	setBitmap(node.attribute("bitmap").as_string());
	setPoint(node.attribute("x").as_float(), node.attribute("y").as_float());
}

void Image::setBitmap(ALLEGRO_BITMAP* bitmap)
{
	_bitmap = bitmap;
	_info = ImageInfo(_bitmap);
}

void Image::setBitmap(string str)
{
	ImageManager* mgr = ImageManager::Instance();
	setBitmap(mgr->getBitmap(str));
}

Point Image::getDrawPoint()
{
	return _p - _info();
}

Point Image::getPoint()
{
	return _p;
}

Point Image::getImageInfo()
{
	return _info();
}

void Image::setPoint(float x, float y)
{
	setPoint(Point(x,y));
}

void Image::setPoint(Point& p)
{
	_p = p;
}

ALLEGRO_BITMAP* Image::getBitmap()
{
	return _bitmap;
}

Word::Word()
{

}

Word::Word(char c, Point p /* = Point */)
{

}

void DrawMode::DrawImage(Image* i)
{
	Point p = i->getPoint();
	al_draw_bitmap(i->getBitmap(), p.x, p.y, 0);
}

void DrawMode::DrawImage(Image* i, float c)
{
	if (c >= 1)
	{
		c = 1;
	}
	Point p = i->getPoint();
	al_draw_tinted_bitmap(i->getBitmap(), al_map_rgba_f(c, c, c ,c), p.x, p.y, 0);
}

void DrawMode::DrawImage(Image* i, Point p)
{
	p = i->getPoint() - p;
	al_draw_bitmap(i->getBitmap(), p.x, p.y , 0);
}

void DrawMode::DrawImage(Image* i, Point p, float c)
{
	p = i->getPoint() - p;
	al_draw_tinted_bitmap(i->getBitmap(),al_map_rgba_f(c, c, c ,c), p.x, p.y, 0);
}

wstring DrawMode::s2ws(string str)
{
	int nSize = MultiByteToWideChar(CP_ACP, 0, (LPCSTR)str.c_str(), str.size(), 0, 0);
	if (nSize <= 0)
	{
		return NULL;
	}
	WCHAR* pwszDst = new WCHAR[nSize + 1];
	if (NULL == pwszDst)
	{
		return NULL;
	}
	MultiByteToWideChar(CP_ACP, 0,(LPCSTR)str.c_str(), str.size(), pwszDst, nSize);
	pwszDst[nSize] = 0;
	if( pwszDst[0] == 0xFEFF) // skip Oxfeff
		for(int i = 0; i < nSize; i ++) 
			pwszDst[i] = pwszDst[i+1]; 
	wstring wcharString(pwszDst);
	delete pwszDst;
	return wcharString;
}