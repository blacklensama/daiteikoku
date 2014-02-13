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
	Image();
	Image(string name, Point p = Point());
	Image(ALLEGRO_BITMAP* bitmap, Point p = Point());
	Image(xml_node& node);
	void setBitmap(string str);
	void setBitmap(ALLEGRO_BITMAP* bitmap);
	void setPoint(Point& p);
	void setPoint(float x, float y);
	Point getDrawPoint();
	Point getPoint();
	Point getImageInfo();
	ALLEGRO_BITMAP* getBitmap();
protected:
private:
	ALLEGRO_BITMAP* _bitmap;
	Point _p;//ÖÐÐÄ×ø±ê
	ImageInfo _info;
};

class Word
{
public:
	Word();
	Word(char c, Point p = Point());
	Word(string s, Point p = Point());
protected:
private:
	wstring _str;
	Point _p;
};

class DrawMode
{
public:
	static void DrawImage(Image* i, float c);
	static void DrawImage(Image* i);
	static void DrawImage(Image* i, Point p);
	static void DrawImage(Image* i, Point p, float c);
protected:
private:
	static wstring s2ws(string str);
};

