#pragma once
#include "stdafx.h"
#include "systemEvent.h"
#include "UIBase.h"
#include "player.h"

class scienceItem
{
public:
	scienceItem(science* s, scienceItem* si = NULL);
	void draw();
	void drawPicture();
	void drawLine();
	void update(systemEvent* e);
	void setPoint(float x, float y);
	Point getPoint();
	bool isInUI(Point p);
	void isMoveIn();
	void isMoveOut();
protected:
private:
	ALLEGRO_BITMAP* _bitmap;
	ALLEGRO_BITMAP* _clickBitmap;
	science* _s;
	bool _isClick;
	bool _isMoveIn;
	vector<scienceItem*> nextNode;
	vector<scienceItem*> UpperNode;
	Point _p;
};

class scienceGlobalUI
{
public:
	void loadthePage(string path);//从xml生成页面
	void draw();
	void update(systemEvent* e);
protected:
private:
	vector<UIBase*> _ui;
};

class scienceUI
{
public:
	void draw();
	void update(systemEvent* e);
protected:
private:
	vector<scienceItem*> item;
	scienceGlobalUI* ui;
};