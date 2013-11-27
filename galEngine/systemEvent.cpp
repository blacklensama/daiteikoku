#include "systemEvent.h"
#include "UIManager.h"
#include "gameManage.h"

SystemEventManager* SystemEventManager::_instance = NULL;

void SystemEventManager::Update()
{
	if (move)
	{
		moveTime++;
	}
	GFUpdate();
	switch (statue)
	{
	case kTrig_PlayMovie:
		break;
	case kTrig_PlayGalGame:
		UIUpdate();
		GameUpdate();
		break;
	case kTrig_AutoPlayGalGame:
		UIUpdate();
		GameUpdate();
		break;
	case kTrig_PlayActive:
		UIUpdate();
		break;
	case kTrig_Menu:
		UIUpdate();
		break;
	default:
		break;
	}
	
	
	RemoveAllTrigger();
}

void SystemEventManager::setStatue(EnumGameStatue e)
{
	statue = e;
}

void globalFunction::addFunction(string& name, string& funcname, string& script)
{
	ASEngine* as = ASEngine::Instance();
	function.insert(make_pair(funcname, as->CompileScript(name, script, funcname)));
}

void globalFunction::update(systemEvent* s)
{
	ASEngine* as = ASEngine::Instance();
	asIScriptContext* ctx = as->getCtx();
	asIScriptFunction* func = NULL;
	switch (s->key)
	{
	case kTrig_Left:
		{
			//as->ListFunctions();
			func = as->getFunc(bind["Left"]);
			//exe script;
			s->remove = true;
			break;
		}
	case kTrig_Down:
		{
			func = as->getFunc(bind["Down"]);
			//exe script;
			s->remove = true;
			break;
		}
	case kTrig_Right:
		{
			func = as->getFunc(bind["Right"]);
			//exe script;
			s->remove = true;
			break;
		}
	case kTrig_Up:
		{
			func = as->getFunc(bind["Up"]);
			//exe script;
			s->remove = true;
			break;
		}
	default:
		break;
	}
	if (func != NULL)
	{
		ctx->Prepare(func);
		ctx->Execute();
	}
	
}

void globalFunction::init(string path)
{
	ASEngine* as = ASEngine::Instance();
	xml_document doc;
	if (!doc.load_file(path.c_str()))
	{
		cout << "can't load the globalfunction xml " << path << endl;
		system("pause");
		return;
	}
	
	xml_node node = doc.child("mousefunction");
	for (xml_node n = node.first_child(); n; n = n.next_sibling())
	{
		if (n.name() == string("function"))
		{
			function.insert(make_pair(n.attribute("funcName").as_string(), as->CompileScript(n.attribute("name").as_string() ,n.attribute("script").as_string(), n.attribute("funcName").as_string())));
		}else if (n.name() == string("bind"))
		{
			bind.insert(make_pair(n.attribute("active").as_string(), n.attribute("funcName").as_string()));
		}
	}
}

void SystemEventManager::GFUpdate()
{
	for (auto i = s.begin(); i != s.end();)
	{
		if (i->second->e == kTrig_LiftMouseMove)
		{
			gf->update(i->second);
			if (i->second->remove == true)
			{
				delete i->second;
				i = s.erase(i);
			}else
			{
				i++;
			}
		}else
		{
			i++;
		}
	}
}

void SystemEventManager::UIUpdate()
{
	UIManager* ui = UIManager::Instance();

	for (auto i = s.begin(); i != s.end();)
	{
		ui->update(i->second);
		if (i->second->remove == true)
		{
			delete i->second;
			i = s.erase(i);
		}else
		{
			i++;
		}
	}
}

void SystemEventManager::GameUpdate()
{
	gameManager* gmr = gameManager::Instance();

	for (auto i = s.begin(); i != s.end(); i++)
	{
		gmr->update(i->second);
	}

}