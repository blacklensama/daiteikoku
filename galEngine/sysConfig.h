#pragma once

#include "stdafx.h"

class sysConfig
{
public:
	inline static void init()
	{
		ifstream infile;
		infile.open("config.ini");
		Json::Reader reader;
		Json::Value root;
		if (!reader.parse(infile, root, false))
		{
			cout << "json error" << endl;
		}
		int size = root.size();
		for (int i = 0; i < size; i++)
		{
			width = root[i]["width"].asInt();
			height = root[i]["height"].asInt();
			interval = root[i]["interval"].asInt();
			alphe = root[i]["alphe"].asInt();
			background1 = root[i]["background1"].asString();
			background1 = root[i]["background2"].asString();
		}
	}
	static void save()
	{
		Json::Value root;
		Json::FastWriter writer;
		Json::Value config;

		config["width"] = width;
		config["height"] = height;
		config["interval"] = interval;
		config["alphe"] = alphe;
		config["background1"] = background1;
		config["background2"] = background2;
		root.append(config);

		string temp = writer.write(root);

		ofstream ofs;
		ofs.open("config.ini");
		ofs << temp;
		ofs.close();
	}
	static int	width;
	static int	height;
	static int	interval;
	static unsigned char alphe;
	static string background1;
	static string background2;
private:
};