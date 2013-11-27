#pragma once

#include "stdafx.h"

class keyManager
{
public:
	keyManager();
	~keyManager();
	static bool keyDown[ALLEGRO_KEY_MAX];
	static bool keyUP[ALLEGRO_KEY_MAX];
	static int mouseX;
	static int mouseY;
	static bool isPress;
	static bool press;
	static bool mouseLeftDown;
	static bool mouseRightDown;
	static void Update();
private:

};