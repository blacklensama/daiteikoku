#include "UIBase.h"
#include "resourceManager.h"
#include "font.h"
#include "UIManager.h"

DIV::DIV()
{
	b = NULL;
	isContent = false;
	_name = "";
	pictureName = inPicture = outPicture = NULL;
	functionName = "";
	x = y = 0;
	priority = 0;
}


DIV::~DIV()
{
	if (b != NULL)
	{
		delete b;
	}
	b = NULL;
}


void DIV::Draw()
{
	al_draw_bitmap(pictureName, x, y, 0);	
	if (b)
	{
		b->Draw();
	}
}

void DIV::setContentUIByName(string name)
{
	if (name == "")
	{
		return;
	}
	UIManager* mgr = UIManager::Instance();
	b = mgr->getUIByName(name);
	b->setPoint(x, y);
}

bool DIV::isInUI(Point s)
{
	ResourceManager* r = ResourceManager::Instance();
	if (s.x > x && s.x < x + al_get_bitmap_width(pictureName))
	{
		if (s.y > y && s.y < y + al_get_bitmap_height(pictureName))
		{
			return true;
		}
	}
	return false;
}

int DIV::Update(systemEvent* s)
{
	if (b)
	{
		/*if (b->Update(s))
		{
			b = NULL;
		}*/
		b->Update(s);
		clickUiContent();
		return 0;
	}
	switch (s->e)
	{
	case kTrig_None:
		if (isInUI(s->p))
		{
			isMoveIn();
		}else
		{
			isMoveOut();
		}
		break;
	case kTrig_LeftClickUp:
		if (isInUI(s->p))
		{
			isClick();
			//s->remove = true;
		}
		break;
	case kTrig_RightClickUp:
		break;
	default:
		break;
	}
	return 0;
}

void DIV::isMoveIn()
{
	pictureName = inPicture;
}

void DIV::isMoveOut()
{
	pictureName = outPicture;
}

void DIV::setPicture(wstring pic)
{
	ResourceManager* r = ResourceManager::Instance();
	pictureName = r->getBitmap(pic);
	inPicture = r->getBitmap(pic);
}

void DIV::setMovePicture(wstring pic)
{
	ResourceManager* r = ResourceManager::Instance();
	outPicture = r->getBitmap(pic);
}

string DIV::getFunction(string name)
{
	return scriptGroup[name];
	/*for (auto i = scriptGroup.begin(); i != scriptGroup.end(); i++)
	{
		if (i->first.find(str) != -1)
		{
			return i->first;
		}
	}
	cout << "can't find the funcName" << endl;
	return NULL;*/
}

void DIV::setfunctionName(string str)
{
	functionName = str;
}

void DIV::addScript(string name, string func, string script)
{
	ASEngine* as = ASEngine::Instance();
	as->CompileScript(name, script, func);
	func = " " + func;
	scriptGroup.insert(make_pair(name, func));
}

bool DIV::setContentUIByTest(UIBase* ui)
{
	if (isContent)
	{
		if (b)
		{
			b->setContentUIByTest(ui);
		}else
		{
			b = ui;
			b->setPoint(x, y);
		}
		return true;
	}
	return false;
}

Point DIV::getPoint()
{
	return Point(x ,y);
}

rectangle DIV::getRect()
{
	ResourceManager* r = ResourceManager::Instance();
	return rectangle(x, y, x + al_get_bitmap_width(pictureName), y + al_get_bitmap_height(pictureName));
}

void DIV::isClick()
{
	ASEngine* as = ASEngine::Instance();
	
	//as->ListFunctions();

	asIScriptContext* ctx = as->getCtx();

	asIScriptFunction *func = as->getFunc(getFunction(_name + "click"));

	if (func == NULL)
	{
		return;
	}
	ctx->Prepare(func);

	ctx->Execute();
}

bool DIV::clickUiContent()
{
	if (b == NULL)
	{
		return true;
	}else
	{
		b->clickUiContent();
		if (getRect().InRectangle(b->getRect()))
		{
			return true;
		}else
		{
			b = NULL;
			return false;
		}
	}
}

Laber::Laber()
{
	isContent = false;
	priority = 0;
	_name = "";
	_text = L"";
	picture = NULL;
	fileName = "";
	b = NULL;
	x = y = 0;
}

void Laber::setName(string str)
{
	_name = str;
}

void Laber::Draw()
{
	if (picture)
	{
		al_draw_bitmap(picture, x, y, 0);
	}
	ALLEGRO_COLOR _color;
	al_color_to_black(&_color);
	al_draw_text(CharFont::getFont(), _color, x, y, 0, _text.c_str());
}

string Laber::getName()
{
	return _name;
}

void Laber::setPoint(float x1, float y1)
{
	x = x1;
	y = y1;
}

void Laber::setPicture(wstring str)
{
	ResourceManager* rmr = ResourceManager::Instance();
	picture = rmr->getBitmap(str);
}

void Laber::addScript(string name, string func, string script)
{
	ASEngine* as = ASEngine::Instance();
	as->CompileScript(name, script, func);
	func = " " + func;
	scriptGroup.insert(make_pair(name, func));
}

string Laber::getFunction(string name)
{
	return scriptGroup[name];
	/*for (auto i = scriptGroup.begin(); i != scriptGroup.end(); i++)
	{
		if (i->first.find(str) != -1)
		{
			return i->first;
		}
	}
	cout << "can't find the funcName" << endl;
	return NULL;*/
}

Point Laber::getPoint()
{
	return Point(x ,y);
}

Pic::Pic()
{
	isContent = false;
	moveFlag = false;
	_bitmap = NULL;
	priority = 0;
	x = 0;
	y = 0;
	b = NULL;
	name = "";
}

Pic::~Pic()
{
	delete b;
}

void Pic::setPicture(wstring s)
{
	ResourceManager* rmr = ResourceManager::Instance();
	_bitmap = rmr->getBitmap(s);
}

void Pic::setName(string str)
{
	name = str;
}

string Pic::getName()
{
	return name;
}

bool Pic::isInUI(Point s)
{
	if (s.x > x2 && s.x < x2 + al_get_bitmap_width(_bitmap))
	{
		if (s.y > y2 && s.y < y2 + al_get_bitmap_height(_bitmap))
		{
			return true;
		}
	}
	return false;
}

int Pic::Update(systemEvent* s)
{
	switch (s->e)
	{
	case kTrig_None:
		{
			if (moveFlag)
			{
				x2 = s->p.x + x;
				y2 = s->p.y + y;
			}
			break;
		}
	case kTrig_LeftClickDown:
		{
			if (isInUI(s->p))
			{
				s->remove = true;
				moveFlag = true;
				x = x1 - s->p.x;
				y = y1 - s->p.y;
			}
			break;
		}
	case kTrig_LeftClickUp:
		{
			if (moveFlag)
			{
				moveFlag = false;
				//判断是否能够进入控件
				UIManager* mgr = UIManager::Instance();
				if (mgr->setUIContent(this))
				{
					return 1;
				}else
					resetPoint();
			}
			break;
		}
	default:
		break;
	}
	return 0;
}

void Pic::Draw()
{
	if (moveFlag)
	{
		al_draw_bitmap(_bitmap, x2, y2, 0);
	}else
	{
		al_draw_bitmap(_bitmap, x1, y1, 0);
	}
}

void Pic::setPoint(float x, float y)
{
	x1 = x2 = x;
	y1 = y2 = y;
}

void Pic::resetPoint()
{
	x2 = x1;
	y2 = y1;
}

void Pic::setNewPoint()
{
	x1 = x2;
	y1 = y2;
}

bool Pic::isInUIContent()
{
	UIManager* mgr = UIManager::Instance();
	return false;
}

Point Pic::getPoint()
{
	return Point(x2 ,y2);
}

rectangle Pic::getRect()
{
	return rectangle(x2, y2, x2+al_get_bitmap_width(_bitmap), y2+al_get_bitmap_height(_bitmap));
}