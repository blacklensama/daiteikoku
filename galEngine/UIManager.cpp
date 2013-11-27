#include "UIManager.h"
#include "systemEvent.h"
#include "rectangle.h"

UIManager* UIManager::_instance = NULL;

UIManager* UIManager::Instance()
{
	if (_instance == NULL)
	{
		_instance = new UIManager();
	}
	return _instance;
}

void UIManager::draw()
{
	for (auto i = _ui.begin(); i != _ui.end(); i++)
	{
		i->second->Draw();
	}
}

void UIManager::update(systemEvent* s)
{
	for (auto i = _ui.begin(); i != _ui.end(); i++)
	{
		i->second->Update(s);
		if (s->remove)
		{
			break;
		}
	}
}

void UIManager::RegisterUI(UIBase* b)
{
	_ui.insert(make_pair(b->getName(), b));
	_uiIndex.insert(b);
}

void UIManager::RemoveUI(string name)
{
	delete _ui[name];
	_ui.erase(name);
}

UIBase* UIManager::getUIByName(string name)
{
	UIBase* temp = _ui[name];
	_ui.erase(name);
	for (auto i = _uiIndex.begin(); i != _uiIndex.end(); i++)
	{
		if ((*i)->getName() == name)
		{
			_uiIndex.erase(i);
			break;
		}
	}
	return temp;
}

void UIManager::init(string filePath)
{
	clearUI();
	xml_document doc;
	if (!doc.load_file(filePath.c_str()))
	{
		cout << "can't load the uixml " << filePath << endl;
		system("pause");
		return;
	}

	xml_node tools = doc.child("UI").child("Items");

	for (xml_node tool = tools.first_child(); tool; tool = tool.next_sibling())
	{
		string kind = tool.attribute("kind").as_string();
		if (kind == "DIV")
		{
			DIV* d = new DIV();
			d->setPoint(tool.attribute("x").as_float(), tool.attribute("y").as_float());
			d->setPicture(xiayuWString::s2ws(tool.attribute("picture").as_string()));
			d->setMovePicture(xiayuWString::s2ws(tool.attribute("movePicture").as_string()));
			d->setName(tool.attribute("name").as_string());
			d->setContentUIByName(tool.attribute("uiName").as_string());
			d->setPriority(tool.attribute("priority").as_int());
			d->setIsContent(tool.attribute("isContent").as_bool());
			for (xml_node node = tool.first_child(); node; node = node.next_sibling())
			{
				d->addScript(node.attribute("name").as_string(), node.attribute("funcName").as_string(), node.attribute("script").as_string());
			}
			RegisterUI(d);
		}else if (kind == "Pic")
		{
			Pic* p = new Pic();
			p->setPoint(tool.attribute("x").as_float(), tool.attribute("y").as_float());
			p->setPicture(xiayuWString::s2ws(tool.attribute("picture").as_string()));
			p->setName(tool.attribute("name").as_string());
			p->setPriority(tool.attribute("priority").as_int());
			p->setIsContent(tool.attribute("isContent").as_bool());
			RegisterUI(p);
		}
	}
}

void UIManager::clearUI()
{
	for (auto i = _ui.begin(); i != _ui.end();)
	{
		delete i->second;
		i = _ui.erase(i);
	}
}

bool UIManager::setUIContent(UIBase* ui)
{
	rectangle r = ui->getRect();
	for (auto i = _ui.begin(); i != _ui.end(); i++)
	{
		if (ui->getName() != i->second->getName())
		{
			if (r.InRectangle(i->second->getRect()))
			{
				if (i->second->setContentUIByTest(ui))
				{
					return true;
				}
			}
		}
	}
	return false;
}