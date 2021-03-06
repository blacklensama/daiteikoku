#include "ImageManager.h"
ImageManager* ImageManager::_instance = NULL;

ImageManager* ImageManager::Instance()
{
	if (_instance == NULL)
	{
		_instance = new ImageManager();
	}
	return _instance;
}

ALLEGRO_BITMAP* ImageManager::getBitmap(string str)
{
	auto i = _bitmap.find(str);
	if (i != _bitmap.end())
	{
		return i->second;
	}
	return NULL;
}

void ImageManager::loadFromFile(string path)
{
	xml_document doc;
	if (doc.load_file(path.c_str()))
	{
		cout << "can't load the xml file " << path << endl;
	}
	auto nodes = doc.select_nodes("//Image");
	for (auto node : nodes)
	{
		_bitmap.insert(make_pair(node.node().attribute("name").as_string(), al_load_bitmap(node.node().attribute("path").as_string())));
	}
}

ImageManager::ImageManager()
{
	loadFromFile("Image/index.xml");
}

ImageManager::~ImageManager()
{
	for (auto i : _bitmap)
	{
		al_destroy_bitmap(i.second);
	}
}

void ImageManager::Release()
{
	delete _instance;
}