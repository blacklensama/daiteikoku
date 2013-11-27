#include "background.h"
#include "ENUM.h"

picture::picture()
{
	_bitmap = NULL;
	al_color_to_black(&color);
	_r = ResourceManager::Instance();
	_draw = false;
}

void picture::setRect(float _x1, float _y1, float _x2, float _y2)
{
	_rect.setRect(_x1, _y1, _x2, _y2);
}

bool picture::inRect(float x1, float y1)
{
	return _rect.InRectangle(x1, y1);
}

void picture::set_bg(script& s)
{
	_bitmap = _r->getBitmap((s.file.ToWString()));
	if (_bitmap == NULL)
	{
		cout << "can't get the bitmap" << endl; 
	}
	_style.set_point(s.x, s.y);
	_style.parse(s.stlye);
	_draw = true;
}

void picture::set_bg(UIscript& s)
{
	_bitmap = _r->getBitmap((s.file.ToWString()));
	if (_bitmap == NULL)
	{
		cout << "can't get the bitmap" << endl; 
	}
	_style.set_point(s.x, s.y);
	_style.parse(s.stlye);
	_draw = true;
}

void picture::changeBitmap(wstring str)
{
	_bitmap = _r->getBitmap(str.c_str());
}

void picture::draw()
{
	if (_draw)
		_style.draw(_bitmap);
}

picture::~picture()
{
	_bitmap = NULL;
	_r = NULL;
}

pictureManager::pictureManager()
{
	for (int i = 0; i < 10; i++)
	{
		_layer.push_back(picture());
	}
}

void picture::update()
{
	if (_draw)
		_style.update();
}

void pictureManager::clear_layer(int i)
{
	if (i != 100)
	{
		_layer[i].set_draw_status(false);
	}else 
	{
		for (int i = 0; i < _layer.size(); i++)
		{
			_layer[i].set_draw_status(false);
		}
	}
}

void pictureManager::set_layer(int i, script& s)
{
	_layer[i].set_bg(s);
}

void pictureManager::set_bg(script& s)
{
	_layer[0].set_bg(s);
}

void pictureManager::draw()
{
	for (int i = 0; i < _layer.size(); i++)
	{
		if (_layer[i].get_draw_status())
		{
			_layer[i].draw();
		}
	}
}

void pictureManager::update()
{
	for (int i = 0; i < _layer.size(); i++)
	{
		if (_layer[i].get_draw_status())
		{
			_layer[i].update();
		}
	}
}

void pictureManager::set_ui_picture(int i, script& s)
{
	_uimanager[i].set_bg(s);
}

void pictureManager::clear_ui(int i)
{
	if (i == 100)
	{
		for (int i = 0; i < _uimanager.size(); i++)
		{
			_uimanager[i].set_draw_status(false);
		}
	}else 
		_uimanager[i].set_draw_status(false);
}

pictureManager::~pictureManager()
{

}

void gameUI::init(wstring str)
{
	UIParse p;
	UIscript s;
	picture p1;
	p.init(str.c_str());
	while (1)
	{
		s = p.read_next_script();
		if (s.kind == PARSE::end)
		{
			break;
		}
		p1.set_bg(s);
		_uipicture.push_back(p1);
	}
}

void gameUI::draw()
{
	for (int i = 0; i < _uipicture.size(); i++)
	{
		_uipicture[i].draw();
	}
}

gameUI::gameUI()
{
}

gameUI::~gameUI()
{
	_uipicture.swap(vector<picture>());
}