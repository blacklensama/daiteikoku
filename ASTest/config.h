#include "stdafx.h"

class Config
{
public:
	static Config* Instance();
	int getWidth();
	int getHeight();
	static void Release();
protected:
	Config();
	void init();
private:
	static Config* _instance;
	int width;
	int height;
};