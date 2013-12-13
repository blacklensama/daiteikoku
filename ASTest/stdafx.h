#pragma once
#include <iostream>
#include "angelscript.h"
#include "scriptstdstring.h"
#include "scriptarray.h"
#include <assert.h>
#include <string>
#include <vector>
#include <map>
#include <crtdbg.h>
#include <windows.h>
#include <conio.h>
#include "pugiconfig.hpp"
#include "pugixml.hpp"
#include "AllegroAddon.h"

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

using namespace std;
using namespace pugi;