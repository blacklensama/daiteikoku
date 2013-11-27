#pragma once

#include "rectangle.h"
#include "resourceManager.h"
#include "parse.h"
#include "style.h"
#include "UIParse.h"

class picture : public xiayuObject
{
public:
	picture();
	void set_bg(script& s);
	void set_bg(UIscript& s);
	void update();
	void draw();
	void setRect(float _x1, float _y1, float _x2, float _y2);
	bool inRect(float x1, float x2);
	bool get_draw_status() {return _draw;}
	void changeBitmap(wstring str);
	void set_draw_status(bool flag){_draw = flag;}
	~picture();
private:
	ALLEGRO_BITMAP* _bitmap;
	ALLEGRO_COLOR color;
	bool _draw;
	style _style;
	ResourceManager* _r;
	rectangle _rect;
};

class gameUI : public xiayuObject
{
public:
	gameUI();
	void init(wstring str);
	void draw();
	void update();//Êó±êÊÂ¼þ
	~gameUI();
private:
	vector<picture> _uipicture;
};

class pictureManager : public xiayuObject
{
public:
	pictureManager();
	void set_layer(int i, script& s);
	void set_bg(script& s);
	void clear_layer(int i);
	void set_ui_picture(int i, script& s);
	void clear_ui(int i);
	void draw();
	void update();
	~pictureManager();
protected:
private:
	picture _bg;
	vector<picture> _layer;
	vector<picture> _uimanager;
};

