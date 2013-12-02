#include "Science.h"
#include "resourceManager.h"
#include "font.h"

scienceItem::scienceItem(science* s, scienceItem* si)
{
	if (si != NULL)
	{
		UpperNode.push_back(si);
	}
	_s = s;
	ResourceManager* r = ResourceManager::Instance();
	_bitmap = r->getBitmap(s->picture);
	_clickBitmap = r->getBitmap(s->clickPicture);
	_isClick = s->learned;
	_p.x = s->x;
	_p.y = s->y;
	for (auto i:s->nodes)
	{
		nextNode.push_back(new scienceItem(i, this));
	}
}

void scienceItem::setPoint(float x, float y)
{
	_p.x = x;
	_p.y = y;
}

Point scienceItem::getPoint()
{
	Point p = _p;
	p.x += al_get_bitmap_width(_bitmap)/2;
	p.y += al_get_bitmap_height(_bitmap)/2;
	return p;
}

void scienceItem::draw()
{
	drawLine();
	drawPicture();
	for (auto i : nextNode)
	{
		i->draw();
	}
}

void scienceItem::drawLine()
{
	ALLEGRO_COLOR c;
	c.a = c.b = c.g = c.r = 1;
	for (auto i:nextNode)
	{
		al_draw_line(getPoint().x, getPoint().y, i->getPoint().x, i->getPoint().y, c, 1);
	}
}

void scienceItem::drawPicture()
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
	al_draw_text(CharFont::getFont(), c, getPoint().x, _p.y + al_get_bitmap_height(_bitmap), ALLEGRO_ALIGN_CENTRE, xiayuWString::s2ws(_s->name).c_str());
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
	if (e->remove == true)
	{
		return;
	}
	switch (e->e)
	{
	case kTrig_LeftClickUp:
		{
			if (isInUI(e->p))
			{
				e->remove = true;
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
	for (auto i : nextNode)
	{
		i->update(e);
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