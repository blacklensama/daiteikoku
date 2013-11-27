#pragma once
#define _DEBUG_ 1
#if _DEBUG
#pragma comment(lib, "json_vc71_libmtd.lib")
#pragma comment(lib, "allegro-5.0.10-monolith-mt-debug.lib")
#else
#pragma comment(lib, "json_vc71_libmt.lib")
#pragma comment(lib, "allegro-5.0.10-monolith-mt.lib")
#endif

#pragma comment(lib, "Dbghelp.lib")
#pragma comment(lib, "angelscriptd.lib")

//windows自带库
#include "ENUM.h"

// TODO: 在此处引用程序需要的其他头文件，allegro库
#include "xiayuAllegroAddon.h"

#include "xiayulib/xiayu.h"

using namespace xiayuLib;

static ALLEGRO_COLOR al_txt_to_color(WCHAR* color)
{
	ALLEGRO_COLOR c;
	c.a = (xy_wchar_to_16(color[6])*16 + xy_wchar_to_16(color[7]))/255;
	c.g = (xy_wchar_to_16(color[0])*16 + xy_wchar_to_16(color[1]))/255;
	c.b = (xy_wchar_to_16(color[2])*16 + xy_wchar_to_16(color[3]))/255;
	c.a = (xy_wchar_to_16(color[4])*16 + xy_wchar_to_16(color[5]))/255;
	return c;
}