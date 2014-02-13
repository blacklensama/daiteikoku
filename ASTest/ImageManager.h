#pragma once
#include "stdafx.h"

class ImageManager
{
public:
	static ImageManager* Instance();
	ALLEGRO_BITMAP* getBitmap(string str);
	static void Release();
protected:
	ImageManager();
	~ImageManager();
private:
	void loadFromFile(string path);
	static ImageManager* _instance;
	map<string,ALLEGRO_BITMAP*> _bitmap;
};