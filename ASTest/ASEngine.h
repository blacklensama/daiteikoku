#pragma once
#include <iostream>
#include "../galEngine/angelscript.h"
#include "../galEngine/scriptstdstring.h"
#include "../galEngine/scripthelper.h"
#pragma comment(lib, "../galEngine/angelscriptd.lib")
using namespace std;
class ASEngine
{
public:
	static ASEngine* Instance();
	void ConfigureEngine(asIScriptEngine* engine);
	void ListFunctions(string mode);
	asIScriptFunction* CompileScript(string name, string script, string funcname, string mode);
	asIScriptFunction* getFunc(string mode, string name);
	asIScriptContext* getCtx();
	void ReleaseMode(string mode);
protected:
	void MessageCallback(const asSMessageInfo &msg);
	ASEngine();
private:
	bool hasCompileErrors;
	asIScriptEngine* engine;
	static ASEngine* _instance;
};