#pragma once
#include "stdafx.h"

class font
{
public:
	static font* Instance();
	ALLEGRO_FONT* getFont();
	static void Release();
	void changeFontSize(int size);
protected:
	font();
	~font();
private:
	static font* _instance;
	ALLEGRO_FONT* _font;
};