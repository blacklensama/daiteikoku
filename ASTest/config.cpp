#include "config.h"

Config* Config::_instance = NULL;

Config* Config::Instance()
{
	if (_instance == NULL)
	{
		_instance = new Config();
	}
	return _instance;
}

int Config::getWidth()
{
	return width;
}

int Config::getHeight()
{
	return height;
}

void Config::Release()
{
	delete _instance;
}

Config::Config()
{
	init();
}

void Config::init()
{
	int r;
	xml_document doc;
	r = doc.load_file("system/config.xml");assert(r==0);
	xml_node node = doc.child("newObj");
	width = node.child("width").first_attribute().as_int();
	height = node.child("height").first_attribute().as_int();
}