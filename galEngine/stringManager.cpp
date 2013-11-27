#include "stringManager.h"
#include "keyManager.h"
#include "resourceManager.h"
#include "sysConfig.h"

void stringManager::init()
{
	ResourceManager* r = ResourceManager::Instance();
	_flags = galStringManager::now;
	_nowUsed = -1;
}

void stringManager::add_string(xiayuWString str)
{
	_flags = now;
	_stringList.push_back(new StringFont(str));
	_nowUsed++;
}

/*
void stringManager::load_the_txt(const char* file)
{
	for (int i = 0; i < _stringList.size(); i++)
	{
		delete _stringList[i];
	}
	_stringList.swap(vector<StringFont*>());
	wifstream infile;
	infile.open(L"test\\start.txt");
	infile.imbue(locale(".936"));
	wstring temp;
	getline(infile, temp);
	StringFont* temp1 = new StringFont();
	temp1->init(temp);
	_stringList.push_back(temp1);
}*/

void stringManager::draw()
{
	if (_flags == galStringManager::now)
	{
		if (_nowUsed != -1)
		{
			_backGround1.draw();
			_stringList[_nowUsed]->draw();
		}
	}else if (_flags == galStringManager::history)
	{
		_backGround2.draw();
		//绘制UI
		//按照历史渲染文字
	}
}

void stringManager::update()
{
	if (_flags == galStringManager::now)
	{
		if (_nowUsed != -1)
		{
			_stringList[_nowUsed]->update();
		}
	}else if (_flags == galStringManager::history)
	{
		//更新UI
	}
}