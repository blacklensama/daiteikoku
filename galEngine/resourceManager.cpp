#include "resourceManager.h"

ResourceManager* ResourceManager::_instance = NULL;

ResourceManager* ResourceManager::Instance()
{
	if (_instance == NULL)
	{
		_instance = new ResourceManager();
	}
	return _instance;
}

ResourceManager::ResourceManager()
{
	init();
}

void ResourceManager::init()
{
	vector<xiayuWString> t = xy_find_filename(L"bitmap\\*.png");
	for (int i = 0; i < t.size(); i++)
	{
		_bitmap.insert(make_pair(t[i].split(L'\\')[1], al_load_bitmap(t[i].ToString().c_str())));
	}
}

ALLEGRO_BITMAP* ResourceManager::getBitmap(wstring name)
{
	return _bitmap[name];
}

ALLEGRO_BITMAP* ResourceManager::getBitmap(string name)
{
	return _bitmap[xiayuWString::s2ws(name)];
}