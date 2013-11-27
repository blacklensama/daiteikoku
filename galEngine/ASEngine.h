#pragma once
#include "stdafx.h"
#include "scriptstdstring.h"
#include "scripthelper.h"

class ASEngine
{
public:
	static ASEngine* Instance();
	asIScriptEngine* engine;
	void ConfigureEngine(asIScriptEngine* engine);
	bool hasCompileErrors;
	asIScriptFunction* CompileScript(string name, string script, string funcname);
	asIScriptFunction* getFunc(string func);
	asIScriptContext* getCtx();
	void ListFunctions();
	void ScriptTest();
protected:
	void MessageCallback(const asSMessageInfo &msg);
	ASEngine();
private:
	void RegisterEnum();
	void RegisterObject();
	static ASEngine* _instance;
	asIScriptContext* ctx;
};