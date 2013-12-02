#include "fps.h"
#include "font.h"
#include "sysConfig.h"
#include "fontString.h"
#include "keyManager.h"
#include "stringManager.h"
#include "resourceManager.h"
#include "parse.h"
#include "gameManage.h"
#include "systemEvent.h"
#include "UIManager.h"
#include "gameInfo.h"
#include "Science.h"
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
	CharFont::loadFont();
	sysConfig::init();
	Parse::init();
	wcout.imbue(locale(".936"));
}
#define _GameDebug_ 2
#if _GameDebug_ == 2
int main(int argc, char** argv)
{
	init();
	ALLEGRO_TIMER* timer;
	ALLEGRO_EVENT_QUEUE* queue;
	ALLEGRO_DISPLAY* display;
	bool redraw = true;
	display = al_create_display(sysConfig::width, sysConfig::height);
	al_set_window_title(display, "test");
	fps f;
	SystemEventManager* sem = SystemEventManager::Instance();
	timer = al_create_timer(1.0/60);
	queue = al_create_event_queue();
	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_mouse_event_source());
	al_register_event_source(queue, al_get_display_event_source(display));
	al_register_event_source(queue, al_get_timer_event_source(timer));
	al_start_timer(timer);
	ResourceManager::Instance();
	SLG_XML_ReSource *s = NULL;
	s = SLG_XML_ReSource::Instance();
	scienceItem* s1 = new scienceItem(s->getScienceByCountry("japan"));
	while (true)
	{
		ALLEGRO_EVENT event;
		al_wait_for_event(queue, &event);
		if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			break;
		if (event.type == ALLEGRO_EVENT_TIMER)
			redraw = true;
		if (event.type == ALLEGRO_EVENT_KEY_DOWN 
			&& event.keyboard.keycode != ALLEGRO_KEY_ESCAPE)
		{
			systemEvent* s = new systemEvent();
			s->e = KTrig_KeyBroadDown;
			s->key = event.keyboard.keycode;
			sem->RegisterTrigger(s);

			keyManager::keyDown[event.keyboard.keycode] = true;
		}
		if (event.type == ALLEGRO_EVENT_KEY_UP 
			&& event.keyboard.keycode != ALLEGRO_KEY_ESCAPE)
		{
			systemEvent* s = new systemEvent();
			s->e = kTrig_KeyBroadUp;
			s->key = event.keyboard.keycode;
			sem->RegisterTrigger(s);

			keyManager::keyDown[event.keyboard.keycode] = false;
			keyManager::keyUP[event.keyboard.keycode] = true;
			keyManager::press = true;
		}
		if (event.type == ALLEGRO_EVENT_KEY_DOWN 
			&& event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
		{
			keyManager::keyDown[ALLEGRO_KEY_ESCAPE] = !keyManager::keyDown[ALLEGRO_KEY_ESCAPE];
		}
		if (event.type == ALLEGRO_EVENT_MOUSE_AXES)
		{
			keyManager::mouseX = event.mouse.x;
			keyManager::mouseY = event.mouse.y;
			systemEvent* s = new systemEvent();
			s->e = kTrig_None;
			s->p.x = event.mouse.x;
			s->p.y = event.mouse.y;
			sem->RegisterTrigger(s);
		}
		if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			systemEvent* s = new systemEvent();
			if (event.mouse.button == 1)
			{
				s->e = kTrig_LeftClickDown;
			}else if (event.mouse.button == 3)
			{
				s->e = kTrig_RightClickDown;
			}
			s->p.x = event.mouse.x;
			s->p.y = event.mouse.y; 
			sem->RegisterTrigger(s);
		}
		if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
		{
			systemEvent* s = new systemEvent();
			if (event.mouse.button == 1)
			{
				keyManager::mouseLeftDown = true;	
				s->e = kTrig_LeftClickUp;
			}else if (event.mouse.button = 3)
			{
				keyManager::mouseRightDown = true;
				s->e = kTrig_RightClickUp;
			}
			s->p.x = event.mouse.x;
			s->p.y = event.mouse.y;
			sem->RegisterTrigger(s);
		}
		if (redraw && al_is_event_queue_empty(queue)) 
		{
			redraw = false;
			f.updata();
			al_clear_to_color(al_map_rgb_f(1, 0, 0));
			f.draw();
			s1->draw();
			al_flip_display();
		}
	}
}

#endif
#if _GameDebug_ == 1
int main(int argc, char** argv)
{
	init();
	ResourceManager::Instance();
	SLG_XML_ReSource *s = NULL;
	s = SLG_XML_ReSource::Instance();
	scienceItem* s1 = new scienceItem(s->getScienceByCountry("japan"));
}
#endif 
#if _GameDebug_ == 0
int main(int argc, char** argv)
{
	init();
	ALLEGRO_TIMER* timer;
	ALLEGRO_EVENT_QUEUE* queue;
	ALLEGRO_DISPLAY* display;
	bool redraw = true;
	display = al_create_display(sysConfig::width, sysConfig::height);
	al_set_window_title(display, "test");
	fps f;
	SystemEventManager* sem = SystemEventManager::Instance();
	timer = al_create_timer(1.0/60);
	queue = al_create_event_queue();
	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_mouse_event_source());
	al_register_event_source(queue, al_get_display_event_source(display));
	al_register_event_source(queue, al_get_timer_event_source(timer));
	al_start_timer(timer);
	ResourceManager::Instance();
	UIManager* ui = UIManager::Instance();
	gameManager* gmr = gameManager::Instance();
	ui->init("ui\\test.xml");
/*
#if _DEBUG_
	ASEngine* as = ASEngine::Instance();
	as->ScriptTest();
	//DIV* d = new DIV();
	//d->init(L"etama6.png", L"etama2.png");
	//d->setName(L"test");
	//d->setPoint(10, 100);
	//ui->RegisterUI(d);
	/ *xiayuInt t;
	stringManager s1;
	s1.init();
	xiayuWString str(L"a.b");
	string str1 = str.ToString();
	ResourceManager* r = ResourceManager::Instance();
	script s = Parse::read_next_script();
	while (1)
	{
		s = Parse::read_next_script();
	}* /
#endif*/
	while (true)
	{
		ALLEGRO_EVENT event;
		al_wait_for_event(queue, &event);
		if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			break;
		if (event.type == ALLEGRO_EVENT_TIMER)
			redraw = true;
		if (event.type == ALLEGRO_EVENT_KEY_DOWN 
			&& event.keyboard.keycode != ALLEGRO_KEY_ESCAPE)
		{
			systemEvent* s = new systemEvent();
			s->e = KTrig_KeyBroadDown;
			s->key = event.keyboard.keycode;
			sem->RegisterTrigger(s);

			keyManager::keyDown[event.keyboard.keycode] = true;
		}
		if (event.type == ALLEGRO_EVENT_KEY_UP 
			&& event.keyboard.keycode != ALLEGRO_KEY_ESCAPE)
		{
			systemEvent* s = new systemEvent();
			s->e = kTrig_KeyBroadUp;
			s->key = event.keyboard.keycode;
			sem->RegisterTrigger(s);

			keyManager::keyDown[event.keyboard.keycode] = false;
			keyManager::keyUP[event.keyboard.keycode] = true;
			keyManager::press = true;
		}
		if (event.type == ALLEGRO_EVENT_KEY_DOWN 
			&& event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
		{
			keyManager::keyDown[ALLEGRO_KEY_ESCAPE] = !keyManager::keyDown[ALLEGRO_KEY_ESCAPE];
		}
		if (event.type == ALLEGRO_EVENT_MOUSE_AXES)
		{
			keyManager::mouseX = event.mouse.x;
			keyManager::mouseY = event.mouse.y;
			systemEvent* s = new systemEvent();
			s->e = kTrig_None;
			s->p.x = event.mouse.x;
			s->p.y = event.mouse.y;
			sem->RegisterTrigger(s);
		}
		if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			systemEvent* s = new systemEvent();
			if (event.mouse.button == 1)
			{
				s->e = kTrig_LeftClickDown;
			}else if (event.mouse.button == 3)
			{
				s->e = kTrig_RightClickDown;
			}
			s->p.x = event.mouse.x;
			s->p.y = event.mouse.y; 
			sem->RegisterTrigger(s);
		}
		if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
		{
			systemEvent* s = new systemEvent();
			if (event.mouse.button == 1)
			{
				keyManager::mouseLeftDown = true;	
				s->e = kTrig_LeftClickUp;
			}else if (event.mouse.button = 3)
			{
				keyManager::mouseRightDown = true;
				s->e = kTrig_RightClickUp;
			}
			s->p.x = event.mouse.x;
			s->p.y = event.mouse.y;
			sem->RegisterTrigger(s);
		}
		if (redraw && al_is_event_queue_empty(queue)) 
		{
			redraw = false;
			f.updata();
			sem->Update();
			//gmr->update();
			al_clear_to_color(al_map_rgb_f(1, 0, 0));
			f.draw();
			gmr->draw();
			ui->draw();
			al_flip_display();
		}
	}
}

#endif 