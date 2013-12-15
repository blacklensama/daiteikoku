#pragma once
#include "stdafx.h"
#include "systemEvent.h"
struct ImageInfo
{
	ImageInfo();
	ImageInfo(ALLEGRO_BITMAP* bitmap);
	Point operator()();
	float w;
	float h;
};

class Image
{
public:
	Image(string name, Point p = Point());
	Image(ALLEGRO_BITMAP* bitmap, Point p = Point());
	void setBitmap(string str);
	void setBitmap(ALLEGRO_BITMAP* bitmap);
	Point getDrawPoint();
	Point getPoint();
	ALLEGRO_BITMAP* getBitmap();
protected:
private:
	ALLEGRO_BITMAP* _bitmap;
	Point _p;//ÖÐÐÄ×ø±ê
	ImageInfo _info;
};

static void DrawImage(Image* i, float c);
static void DrawImage(Image* i);
static void DrawImage(Image* i, Point p);
static void DrawImage(Image* i, Point p, float c);

