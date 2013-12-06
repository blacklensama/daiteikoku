#include "ASEngine.h"
#include <assert.h>

ASEngine* ASEngine::_instance = NULL;

ASEngine* ASEngine::Instance()
{
	if (_instance == NULL)
	{
		_instance = new ASEngine();
	}
	return _instance;
}

ASEngine::ASEngine()
{
	int r;

	engine = asCreateScriptEngine(ANGELSCRIPT_VERSION);

	if (engine == NULL)
	{
		cout << "Failed to create script engine." << endl;
	}

	r = engine->SetMessageCallback(asMETHOD(ASEngine, MessageCallback), this, asCALL_THISCALL); assert( r >= 0 );
	engine->SetEngineProperty(asEP_ALLOW_UNSAFE_REFERENCES, true);
	ConfigureEngine(engine);
}

void ASEngine::MessageCallback(const asSMessageInfo &msg)
{
	const char *type = "ERR ";
	if( msg.type == asMSGTYPE_WARNING ) 
		type = "WARN";
	else if( msg.type == asMSGTYPE_INFORMATION ) 
		type = "INFO";

	cout << msg.section << " (" << msg.row << ", " << msg.col << ") : " << type << " : " << msg.message << endl;

	if( msg.type == asMSGTYPE_ERROR )
		hasCompileErrors = true;
}

void ASEngine::ConfigureEngine(asIScriptEngine* engine)
{

}

void ASEngine::ListFunctions(string mode)
{
	{
		asUINT n;

		// List the application registered functions
		cout << "Application functions:" << endl;
		for( n = 0; n < (asUINT)engine->GetGlobalFunctionCount(); n++ )
		{
			asIScriptFunction *func = engine->GetGlobalFunctionByIndex(n);

			// Skip the functions that start with _ as these are not meant to be called explicitly by the user
			if( func->GetName()[0] != '_' )
				cout << " " << func->GetDeclaration() << endl;
		}

		// List the user functions in the module
		asIScriptModule *mod = engine->GetModule(mode.c_str());
		if( mod )
		{
			cout << endl;
			cout << "User functions:" << endl;
			for( n = 0; n < (asUINT)mod->GetFunctionCount(); n++ )
			{
				asIScriptFunction *func = mod->GetFunctionByIndex(n);
				cout << " " << func->GetDeclaration() << endl;
			}
		}
	}
}

asIScriptFunction* ASEngine::CompileScript(string name, string script, string funcname, string mode)
{
	int r;

	asIScriptModule *mod = engine->GetModule(mode.c_str(), asGM_CREATE_IF_NOT_EXISTS);

	asIScriptFunction* func = 0;
	r = mod->CompileFunction(name.c_str(), script.c_str(), 0, asCOMP_ADD_TO_MODULE, &func);assert(r>0);
	return func;
}

asIScriptFunction* ASEngine::getFunc(string mode, string name)
{
	return engine->GetModule(mode.c_str())->GetFunctionByDecl(name.c_str());
}

asIScriptContext* ASEngine::getCtx()
{
	return engine->CreateContext();
}

void ASEngine::ReleaseMode(string mode)
{
	engine->DiscardModule(mode.c_str());
}