#pragma once

#include "fontString.h"
#include "background.h"

class stringManager : public xiayuObject
{
public:
	stringManager()
	{
		_backGround1.init(L"UIScript\\background1.txt");
		_backGround2.init(L"UIScript\\background2.txt");
		_nowUsed = -1;
	}
	void init();
	void add_string(xiayuWString str);
	void draw();
	void update();
	void set_flag(galStringManager i){ _flags = i;}
	galStringManager get_flag(){ return _flags;}
	galString get_string_status() 
	{
		if (_nowUsed == -1)
		{
			return Finish;
		}
		return _stringList[_nowUsed]->getStatue();
	}
	void set_string_status(galString f) 
	{
		_stringList[_nowUsed]->all_to_black();
		_stringList[_nowUsed]->setStatus(f);
	}
	~stringManager()
	{
		for (auto i = _stringList.begin(); i != _stringList.end(); i++)
		{
			delete *i;
		}
		_stringList.clear();
	}
private:
	vector<StringFont*> _stringList;
	xiayuString _nowTxt;
	int _nowUsed;
	galStringManager _flags;
	gameUI _backGround1;
	gameUI _backGround2;
	int a[10];
};