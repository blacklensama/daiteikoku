#include "Science.h"
#include "resourceManager.h"
#include "font.h"

scienceItem::scienceItem(science* s)
{
	_s = s;
	ResourceManager* r = ResourceManager::Instance();
	_bitmap = r->getBitmap(s->picture);
	_clickBitmap = r->getBitmap(s->clickPicture);
}

void scienceItem::setPoint(float x, float y)
{
	_p.x = x;
	_p.y = y;
}

void scienceItem::draw()
{
	if (_isClick || _isMoveIn)
	{
		al_draw_bitmap(_clickBitmap, _p.x, _p.y, 0);
	}else
	{
		al_draw_bitmap(_bitmap, _p.x, _p.y, 0);
	}
	ALLEGRO_COLOR c;
	c.a = c.b = c.g = c.r = 1;
	al_draw_text(CharFont::getFont(), c, _p.x, _p.x + al_get_bitmap_height(_bitmap), 0, xiayuWString::s2ws(_s->name).c_str());
}

bool scienceItem::isInUI(Point p)
{
	if (p.x > _p.x && p.x < _p.x + al_get_bitmap_width(_bitmap))
	{
		if (p.y > _p.y && p.y < _p.y + al_get_bitmap_height(_bitmap))
		{
			return true;
		}
	}
	return false;
}

void scienceItem::isMoveIn()
{
	_isMoveIn = true;
}

void scienceItem::isMoveOut()
{
	_isMoveIn = false;
}

void scienceItem::update(systemEvent* e)
{
	switch (e->e)
	{
	case kTrig_LeftClickUp:
		{
			if (isInUI(e->p))
			{
				if (!_isClick)
				{
					_isClick = true;
					//¿ÛÇ®
				}
			}
			break;
		}
	case kTrig_None:
		{
			if (isInUI(e->p))
			{
				isMoveIn();
			}else
			{
				isMoveOut();
			}
			break;
		}
	default:
		break;
	}
}

void scienceGlobalUI::loadthePage(string path)
{

}

void scienceGlobalUI::draw()
{
	for (auto i : _ui)
	{
		i->Draw();
	}
}

void scienceGlobalUI::update(systemEvent* e)
{
	for (auto i : _ui)
	{
		i->Update(e);
	}
}

void scienceUI::draw()
{
	ui->draw();
	for (auto i : item)
	{
		i->draw();
	}
}

void scienceUI::update(systemEvent* e)
{
	ui->update(e);
	for (auto i : item)
	{
		i->update(e);
	}
}