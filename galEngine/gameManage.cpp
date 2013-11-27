#include "gameManage.h"
#include "parse.h"
#include "keyManager.h"

gameManager* gameManager::_instance = NULL;

gameManager* gameManager::Instance()
{
	if (_instance == NULL)
	{
		_instance = new gameManager();
	}
	return _instance;
}

gameManager::gameManager()
{
}

gameManager::~gameManager()
{

}

void gameManager::update(systemEvent* e)
{
	switch (e->e)
	{
	case kTrig_KeyBroadUp:
	case kTrig_LeftClickUp:
		update();
	default:
		break;
	}
}

void gameManager::update()
{
	//if (keyManager::press)
	//{
		//keyManager::press = false;
		if (_str.get_string_status() == galString::oneToOne)
		{
			_str.set_string_status(galString::Finish);
		}else
		{
			script s = Parse::read_next_script();
			if (s.kind == PARSE::draw)
			{
				_pic.set_layer(s.layer, s);
			}else if (s.kind == PARSE::drawbg)
			{
				_pic.set_bg(s);
			}else if (s.kind == PARSE::print)
			{
				_str.add_string(s.str);
			}else if (s.kind == PARSE::clear)
			{
				_pic.clear_layer(s.layer);
			}
		}
	//}
}

void gameManager::draw()
{
	_pic.update();
	_str.update();
	_pic.draw();
	_str.draw();
}