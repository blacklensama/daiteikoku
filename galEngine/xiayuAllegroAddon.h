#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_audio.h"
#include "allegro5/allegro_primitives.h"
#include "allegro5/allegro_ttf.h"
#include "allegro5/allegro_acodec.h"
#include "allegro5/utf8.h"
#include "allegro5/allegro_physfs.h"
#include "allegro5/allegro_windows.h"
#include "allegro5/allegro_direct3d.h"

static void al_draw_text(const ALLEGRO_FONT* font, ALLEGRO_COLOR color, float x, float y, int flags, uint16_t const *text)
{
	ALLEGRO_USTR* ustr = al_ustr_new_from_utf16(text);
	assert(text);
	al_draw_ustr(font, color, x, y, flags, ustr);
	al_ustr_free(ustr);
}

inline void al_draw_text(const ALLEGRO_FONT* font, ALLEGRO_COLOR color, float x, float y, int flags,const WCHAR *text)
{
	ALLEGRO_USTR* ustr = al_ustr_new_from_utf16((uint16_t*)text);
	assert(text);
	al_draw_ustr(font, color, x, y, flags, ustr);
	al_ustr_free(ustr);
}

static void al_color_to_white(ALLEGRO_COLOR* color)
{
	color->a = 0;
	color->b = 0;
	color->g = 0;
	color->r = 0;
}
static void al_add_color(ALLEGRO_COLOR* color, float r, float g, float b, float a)
{
	if (color->a < 1)
		color->a += a;
	if (color->a > 1)
		color->a = 1;
	if (color->b < 1)
		color->b += b;
	if (color->b > 1)
		color->b = 1;
	if (color->g < 1)
		color->g += g;
	if (color->g > 1)
		color->g = 1;
	if (color->r < 1)
		color->r += r;
	if (color->r > 1)
		color->r = 1;
}
static void al_add_color(ALLEGRO_COLOR* color, float i)
{
	if (color->a < 1)
	{
		color->a += i;
		color->b = 0;
		color->g = 0;
		color->r = 0;
	}
	if (color->a >= 1)
	{
		color->a = 1;
		color->b = 0;
		color->g = 0;
		color->r = 0;
	}
}

static void al_color_to_black(ALLEGRO_COLOR* color)
{
	color->a = 1;
	color->b = 0;
	color->g = 0;
	color->r = 0;
}

/*
static ALLEGRO_COLOR al_txt_to_color(WCHAR* color)
{
	ALLEGRO_COLOR c;
	c.a = (xy_wchar_to_16(color[6])*16 + xy_wchar_to_16(color[7]))/255;
	c.g = (xy_wchar_to_16(color[0])*16 + xy_wchar_to_16(color[1]))/255;
	c.b = (xy_wchar_to_16(color[2])*16 + xy_wchar_to_16(color[3]))/255;
	c.a = (xy_wchar_to_16(color[4])*16 + xy_wchar_to_16(color[5]))/255;
	return c;
}*/