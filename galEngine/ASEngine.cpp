#include "ASEngine.h"
#include "ASTestFunction.h"
#include "systemEvent.h"
#include "UIBase.h"


void PrintString(string &str)
{
	cout << str << endl;
}


void PrintString_Generic(asIScriptGeneric *gen)
{
	cout << 1 << endl;
	string *str = (string*)gen->GetArgAddress(0);
	PrintString(*str);
}

void SetGameStatue(EnumGameStatue e)
{
	SystemEventManager* sem = SystemEventManager::Instance();
	sem->setStatue(e);
	cout << e << endl;
}

struct testMessage
{
	int i;
	int b;
};

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

void ASEngine::ConfigureEngine(asIScriptEngine* engine)
{
	int r;

	RegisterStdString(engine);
	RegisterEnum();
	RegisterObject();
	if( !strstr(asGetLibraryOptions(), "AS_MAX_PORTABILITY") )
	{
		// Register the functions that the scripts will be allowed to use.
		// Note how the return code is validated with an assert(). This helps
		// us discover where a problem occurs, and doesn't pollute the code
		// with a lot of if's. If an error occurs in release mode it will
		// be caught when a script is being built, so it is not necessary
		// to do the verification here as well.
		r = engine->RegisterGlobalFunction("void Print(string &in)", asFUNCTION(PrintString), asCALL_CDECL); assert( r >= 0 );
		r = engine->RegisterGlobalFunction("void setGameStatus(EnumGameStatue e)", asFUNCTION(SetGameStatue), asCALL_CDECL);assert(r >= 0);
	}
	else
	{
		r = engine->RegisterGlobalFunction("void Print(string &in)", asFUNCTION(PrintString_Generic), asCALL_GENERIC); assert( r >= 0 );
	}

	ctx = engine->CreateContext();
	if( ctx == 0 ) 
	{
		cout << "Failed to create the context." << endl;
		engine->Release();
	}
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

asIScriptFunction* ASEngine::CompileScript(string name, string script, string funcname)
{
	int r;

	asIScriptModule* mod = engine->GetModule(0, asGM_CREATE_IF_NOT_EXISTS);
	asIScriptFunction *func = 0;
	r = mod->CompileFunction(name.c_str(), script.c_str(), 0, asCOMP_ADD_TO_MODULE, &func);
	if( r < 0 )
	{
		cout << "Failed to add function" << endl;
		return NULL;
	}else
	{
		if( mod->GetFunctionByName(func->GetName()) == 0 )
		{
			mod->RemoveFunction(func);
			cout << "Another function with that name already exists." << endl;
		}
		else
		{
			cout << "Function added. " << "functionName:" << func->GetName() << endl;
		}
	}
	return func;
}

asIScriptContext* ASEngine::getCtx()
{
	return engine->CreateContext();
}

asIScriptFunction* ASEngine::getFunc(string name)
{
	name = " " + name;
	return engine->GetModule(0)->GetFunctionByDecl(name.c_str());
}

void ASEngine::ListFunctions()
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
		asIScriptModule *mod = engine->GetModule(0);
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

void ASEngine::RegisterEnum()
{
	engine->RegisterEnum("EnumGameStatue");
	engine->RegisterEnumValue("EnumGameStatue", "kTrig_PlayMovie", kTrig_PlayMovie);
	engine->RegisterEnumValue("EnumGameStatue", "kTrig_PlayGalGame", kTrig_PlayGalGame);
	engine->RegisterEnumValue("EnumGameStatue", "kTrig_PlayActive", kTrig_PlayActive);
	engine->RegisterEnumValue("EnumGameStatue", "kTrig_Menu", kTrig_Menu);
}

void ASEngine::RegisterObject()
{
	int r;
	r = engine->RegisterObjectType("UIMessage", sizeof(UIMessage), asOBJ_VALUE| asOBJ_POD| asOBJ_APP_CLASS);assert(r>=0);
	r = engine->RegisterObjectProperty("UIMessage", "int color", offsetof(UIMessage, color));assert(r >=0);
	r = engine->RegisterObjectProperty("UIMessage", "int time", offsetof(UIMessage, time));assert(r >=0);
}

void ASEngine::ScriptTest()
{
	int r;
	const char *script = "UIMessage ScriptTest(UIMessage temp)"
						"{"
						"  temp.color = 10;"
						"  temp.time = 10;"
						"  return temp;"
						"}";
	int i = 10;
	asIScriptModule* mod = engine->GetModule(0, asGM_CREATE_IF_NOT_EXISTS);
	asIScriptFunction *func = 0;
	r = mod->CompileFunction("testscript", script, 0, asCOMP_ADD_TO_MODULE, &func);
	if( r < 0 )
	{
		cout << "Failed to add function" << endl;
	}else
	{
		if( mod->GetFunctionByName(func->GetName()) == 0 )
		{
			mod->RemoveFunction(func);
			cout << "Another function with that name already exists." << endl;
		}
		else
		{
			cout << "Function added. " << endl;
		}
	}
	UIMessage temp;
	temp.color = 1;
	temp.time = 1;
	ctx->Prepare(func);
	ctx->SetArgObject(0, &temp);
	ctx->Execute();
	UIMessage* t = (UIMessage*)ctx->GetReturnObject();
	cout << i << endl;
}