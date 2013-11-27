#pragma once
#include "stdafx.h"
#include "systemEvent.h"
#include "ASEngine.h"
#include "rectangle.h"

class UIBase
{
public:
	virtual string getName() = 0;
	virtual void Draw() = 0;
	virtual int Update(systemEvent* s) = 0;
	virtual void isClick() = 0;
	virtual bool isInUI(Point s) = 0;
	virtual void isMoveIn() = 0;
	virtual void isMoveOut() = 0;
	virtual void enter() = 0;
	virtual void exit() = 0;
	virtual void setContentUIByName(string name) = 0;
	virtual void setPoint(float x1, float y1) = 0;
	virtual ~UIBase(){};
	virtual int getPriority() = 0;
	virtual void setPriority(int x) = 0;
	virtual bool setContentUIByTest(UIBase* ui) = 0;
	virtual Point getPoint() = 0;
	virtual rectangle getRect() = 0;
	virtual void setIsContent(bool b) = 0;
	virtual bool clickUiContent() = 0;
private:
};

class DIV : public UIBase
{
public:
	DIV();
	string getName()
	{
		return _name;
	}
	void setPicture(wstring pic);
	void setMovePicture(wstring pic);
	void setName(string str)
	{
		_name = str;
	}
	void setfunctionName(string str);
	void setScript(string str);
	void addScript(string name, string func, string script);
	void Draw();
	int Update(systemEvent* s);
	void isClick();
	bool isInUI(Point s);
	void isMoveIn();
	void isMoveOut();
	void setContentUIByName(string name);
	void enter(){};
	void exit(){};
	void setPoint(float x1, float y1)
	{
		x = x1;
		y = y1;
	}
	void setPriority(int x){ priority = x;}
	int getPriority(){return priority;}
	bool setContentUIByTest(UIBase* ui);
	void setIsContent(bool b){isContent = b;}
	bool clickUiContent();
	rectangle getRect();
	Point getPoint();
	~DIV();
protected:
private:
	bool isContent;
	int priority;
	string getFunction(string);
	string _name;
	ALLEGRO_BITMAP* pictureName;
	ALLEGRO_BITMAP* inPicture;
	ALLEGRO_BITMAP* outPicture;
	map<string, string> scriptGroup;
	string functionName;
	UIBase* b;
	float x;
	float y;
};

class Laber: public UIBase
{
public:
	Laber();
	void setContentUIByName(string name){};
	string getName();
	void setText(wstring str);
	void setName(string str);
	void setPicture(wstring p);
	void setPoint(float x, float y);
	void addScript(string name, string func, string script);
	void setPicture();
	void isClick(){};
	int Update(systemEvent* s){return 0;}
	void Draw();
	void setPriority(int x){ priority = x;}
	int getPriority(){return priority;}
	bool setContentUIByTest(UIBase* ui){ return false;}
	Point getPoint();
	void setIsContent(bool b){isContent = b;}
	bool clickUiContent(){return false;}
	~Laber(){};
protected:
private:
	bool isContent;
	int priority;
	string getFunction(string);
	string _name;
	wstring _text;
	map<string, string> scriptGroup;
	ALLEGRO_BITMAP* picture;
	string fileName;
	UIBase* b;
	float x;
	float y;
};

class Pic: public UIBase
{
public:
	Pic();
	void setContentUIByName(string name){};
	string getName();
	int Update(systemEvent* s);
	void setName(string str);
	void setPicture(wstring s);
	void isMoveIn(){};
	void isMoveOut(){};
	bool isInUI(Point s);
	void isClick(){};
	void save();
	void Draw();
	void setPoint(float x, float y);
	void enter(){};
	void exit(){};
	bool isInUIContent();
	void setPriority(int x){ priority = x;}
	int getPriority(){return priority;}
	bool setContentUIByTest(UIBase* ui){ return false;}
	Point getPoint();
	rectangle getRect();
	void setIsContent(bool b){isContent = b;}
	bool clickUiContent(){return false;}
	~Pic();
protected:
private:
	bool isContent;
	void resetPoint();
	void setNewPoint();
	int priority;
	UIBase* b;
	string name;
	ALLEGRO_BITMAP* _bitmap;//原始图片
	bool moveFlag;
	float x;//用于拖拽记入鼠标和图片的相对位移
	float y;
	float x1;//用于记录原始坐标或者是修改以后的坐标
	float y1;
	float x2;//用于记入绘制坐标
	float y2;
};