#pragma once

#include "stdafx.h"

class ResourceManager
{
public:
	static ResourceManager* Instance();
	ALLEGRO_BITMAP* getBitmap(wstring name);
	ALLEGRO_BITMAP* getBitmap(string name);
	void init();
	~ResourceManager();
protected:
	ResourceManager();
private:
	static ResourceManager* _instance;
	map<wstring, ALLEGRO_BITMAP*> _bitmap;
};