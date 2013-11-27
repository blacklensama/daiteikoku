#pragma once

#include "background.h"
#include "stringManager.h"
#include "systemEvent.h"

class gameManager
{
public:
	static gameManager* Instance();
	~gameManager();
	void update();
	void update(systemEvent* e);
	void draw();
protected:
	gameManager();
private:
	static gameManager* _instance;
	pictureManager _pic;
	stringManager _str;
	galStatue _status;
};