#include "behavior_tree.h"
#include "EnumUtil.h"
#include<stdlib.h>  
#include "Widget.h"
#include "ImageManager.h"
#define _DEBUGMODE_ 0
void init()
{
	al_init();
	al_install_mouse();
	al_install_keyboard();
	al_install_audio();
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_acodec_addon();
	al_init_primitives_addon();
	EnumUtil::init();
}

void Release()
{
	ASEngine::Release();
	BlackBoardForScript::Release();
	ImageManager::Release();
	al_shutdown_font_addon();
	al_shutdown_image_addon();
	al_shutdown_primitives_addon();
	al_shutdown_ttf_addon();
	al_uninstall_audio();
	al_uninstall_mouse();
	al_uninstall_keyboard();
	al_uninstall_system();
}

#if _DEBUGMODE_ == 1
int main()
{
	string str = "ÄãºÃ";
}
#endif
#if _DEBUGMODE_ == 0
int main()
{
	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF|_CRTDBG_ALLOC_MEM_DF);
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
	init();
	ASEngine* en = ASEngine::Instance();
	en->scriptTest("test.as");

	BehaviorTreeObject obj;
	auto i = obj.loadFromXml("btree/test.xml");
	i->Update(NULL);
	delete i;
	//WidgetInfo w("test.xml");
	//w.tick();
	Release();
}
#endif