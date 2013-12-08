#pragma once
#include "stdafx.h"
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
	void scriptTest(string filepath);
protected:
	void MessageCallback(const asSMessageInfo &msg);
	ASEngine();
private:
	void RegisteClass();
	void RegisteFunction();
	void RegisteEnum();
	bool hasCompileErrors;
	asIScriptEngine* engine;
	static ASEngine* _instance;
};