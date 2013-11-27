#pragma once

#include "fontString.h"
#include "keyManager.h"

StringFont::StringFont(wstring str)
{
	_starttime = sysConfig::interval;
	_startnum = 0;
	_flags = galString::oneToOne;
	float x, y;
	x = 100;
	y = 400;
	for (int i = 0; i < 40; i++)
	{
		_effect.push_back(new CharFont());
		_effect[i]->setPoint(x, y);
		x += 30;
		if (x > 700)
		{
			y += 30;
			x = 100;
		}
	}
	init(str);
}

void StringFont::init(wstring str)
{
	_nowRead = str;
	/*for (int i = 0; i < str.size(); i++)
	{
		_effect[i]->init(str[i]);
	}*/
	int i = 0;
	for (wstring::iterator itor = str.begin(); itor != str.end(); itor++)
	{
		_effect[i]->init(*itor);
		i++;
		//cout << *itor << endl;
	}
}

void StringFont::init(xiayuWString& str)
{
	init(str.ToWString());
}

void StringFont::draw()
{
	for (int i = 0; i < _nowRead.getSize(); i++)
	{
		_effect[i]->draw();
	}
}

void StringFont::draw(float y)
{
	for (int i = 0; i < _nowRead.getSize(); i++)
	{
		_effect[i]->draw(y);
	}
}

void StringFont::update()
{
	/*if (keyManager::press)
	{
		keyManager::press = false;
		_flags = galString::Finish;
		all_to_black();
	}*/
	if (_flags == galString::oneToOne)
	{
		for (int i = 0; i < _startnum; i++)
		{
			if (_startnum == _effect.size())
			{
				_flags = galString::Finish;
			}
			_effect[i]->updata();
		}
		_starttime--;
		if (_starttime == 0)
		{
			_starttime = sysConfig::interval;
			_startnum++;
		}
	}
	if (_flags == galString::Finish)
	{
		//等待效果更新
	}
}

void StringFont::all_to_black()
{
	for (int i = 0; i < _effect.size(); i++)
	{
		_effect[i]->ToBlack();
	}
}