#include "behavior_tree.h"
#include "EnumUtil.h"
#include "config.h"
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
	ASEngine::Instance();
	Config::Instance();
	NodeMgr::Instance();
}

void Release()
{
	NodeMgr::Release();
	WidgetMgr::Release();
	Config::Release();
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
	init();
	//ASEngine* en = ASEngine::Instance();
	//en->scriptTest("test.as");
	
	NodeMgr* mgr = NodeMgr::Instance();

	mgr->addNode(new ActionNode("test", Running));
	mgr->changeNodeStatic("test1", Failure);

	Release();
}
#endif
#if _DEBUGMODE_ == 0
int main()
{
	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF|_CRTDBG_ALLOC_MEM_DF);
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
	init();
	ALLEGRO_TIMER* timer;
	ALLEGRO_EVENT_QUEUE* queue;
	ALLEGRO_DISPLAY* display;
	bool redraw = true;
	
	Config* config = Config::Instance();
	//display = al_create_display(config->getWidth(), config->getHeight());

	display = al_create_display(800,600);

	al_set_window_title(display, "´óµÛ¹ú");

	timer = al_create_timer(1.0/60);
	queue = al_create_event_queue();
	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_mouse_event_source());
	al_register_event_source(queue, al_get_display_event_source(display));
	al_register_event_source(queue, al_get_timer_event_source(timer));
	al_start_timer(timer);

	ImageManager* imr = ImageManager::Instance();

	WidgetMgr* mgr = WidgetMgr::Instance();

	BlackBoardForScript* blackboard = BlackBoardForScript::Instance();
	mgr->loadFromXml("test.xml");
	

	while (true)
	{
		ALLEGRO_EVENT event;
		al_wait_for_event(queue, &event);

		if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			break;
		if (event.type == ALLEGRO_EVENT_TIMER)
			redraw = true;
		if (event.type == ALLEGRO_EVENT_KEY_DOWN && event.keyboard.keycode != ALLEGRO_KEY_ESCAPE)
		{
			systemEvent s;
			s.e = KTrig_KeyBroadDown;
			s.key = event.keyboard.keycode;
			blackboard->addSystemEvent(s);
		}
		if (event.type == ALLEGRO_EVENT_KEY_UP && event.keyboard.keycode != ALLEGRO_KEY_ESCAPE)
		{
			systemEvent s;
			s.e = kTrig_KeyBroadUp;
			s.key = event.keyboard.keycode;
			blackboard->addSystemEvent(s);
		}
		if (event.type == ALLEGRO_EVENT_MOUSE_AXES)
		{
			systemEvent s;
			s.p.x = event.mouse.x;
			s.p.y = event.mouse.y;
			s.e = kTrig_None;
			blackboard->addSystemEvent(s);
		}
		if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			systemEvent s;
			if (event.mouse.button == 1)
			{
				s.e = kTrig_LeftClickDown;
			}else if (event.mouse.button == 3)
			{
				s.e = kTrig_RightClickDown;
			}
			s.p.x = event.mouse.x;
			s.p.y = event.mouse.y;
			blackboard->addSystemEvent(s);
		}
		if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
		{
			systemEvent s;
			if (event.mouse.button == 1)
			{
				s.e = kTrig_LeftClickUp;
			}else if (event.mouse.button == 3)
			{
				s.e = kTrig_RightClickUp;
			}
			s.p.x = event.mouse.x;
			s.p.y = event.mouse.y;
			blackboard->addSystemEvent(s);
		}
		if (redraw && al_is_event_queue_empty(queue)) 
		{
			redraw = false;
			al_clear_to_color(al_map_rgb_f(1, 0, 0));
			mgr->tick();
			blackboard->removeAllEvent();
			al_flip_display();
		}
	}

	Release();
}
#endif