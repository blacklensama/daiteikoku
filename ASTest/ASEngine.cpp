#include "ASEngine.h"
#include "ASFunction.h"

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
	RegisterStdString(engine);
	RegisteEnum();
	RegisteClass();
	RegisteFunction();
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

asIScriptFunction* ASEngine::CompileScript(string name, string script, string mode, string funcname)
{
	int r;

	asIScriptModule *mod = engine->GetModule(mode.c_str(), asGM_ALWAYS_CREATE);
	r = mod->AddScriptSection(name.c_str(), &script[0]);assert(r >= 0);
	r = mod->Build();assert(r>=0);
	return mod->GetFunctionByDecl(funcname.c_str());
}

asIScriptFunction* ASEngine::getFunc(string mode, string name)
{
	return engine->GetModule(mode.c_str())->GetFunctionByDecl(name.c_str());
}

asIScriptContext* ASEngine::getCtx()
{
	return engine->CreateContext();
}

void ASEngine::RegisteClass()
{
	int r;

	//Register Point struct
	r = engine->RegisterObjectType("Point", sizeof(Point), asOBJ_APP_CLASS|asOBJ_POD|asOBJ_VALUE);assert(r >= 0);
	r = engine->RegisterObjectProperty("Point", "float x", asOFFSET(Point, x));assert(r >= 0);
	r = engine->RegisterObjectProperty("Point", "float y", asOFFSET(Point, y));assert(r >= 0);

	//register systemEvent struct
	r = engine->RegisterObjectType("systemEvent", sizeof(systemEvent),asOBJ_APP_CLASS|asOBJ_POD|asOBJ_VALUE);assert(r>=0);
	r = engine->RegisterObjectProperty("systemEvent", "EnumTriggerType e", asOFFSET(systemEvent, e));assert(r >= 0);
	r = engine->RegisterObjectProperty("systemEvent", "Point p", asOFFSET(systemEvent, p));assert(r >= 0);
	r = engine->RegisterObjectProperty("systemEvent", "int key", asOFFSET(systemEvent, key));assert(r >= 0);

	//register BlackBoard class
	r = engine->RegisterObjectType("BlackBoard", 0, asOBJ_REF|asOBJ_NOCOUNT);assert(r>=0);
	r = engine->RegisterObjectMethod("BlackBoard", "int getListLength()", asMETHOD(BlackBoardForScript, getListLength), asCALL_THISCALL);assert(r>=0);
	r = engine->RegisterObjectMethod("BlackBoard", "void removeSystemEventByIndex(int num)", asMETHOD(BlackBoardForScript, removeSystemEventByIndex), asCALL_THISCALL);assert(r>=0);
	r = engine->RegisterObjectMethod("BlackBoard", "systemEvent getSystemEventByIndex(int num)", asMETHOD(BlackBoardForScript, getSystemEventByIndex), asCALL_THISCALL);assert(r>=0);
	//r = engine->RegisterGlobalProperty("BlackBoard@ blackBoard", b);assert(r>=0);
	r = engine->RegisterObjectBehaviour("BlackBoard",  asBEHAVE_FACTORY, "BlackBoard@ f()", asFUNCTION(getBlackBoard), asCALL_CDECL);assert(r >= 0);


	//register WidgetMgr class
	r = engine->RegisterObjectType("WidgetMgr", 0, asOBJ_REF|asOBJ_NOCOUNT);assert(r>=0);
	r = engine->RegisterObjectBehaviour("WidgetMgr",  asBEHAVE_FACTORY, "WidgetMgr@ f()", asFUNCTION(getWidgetMgr()), asCALL_CDECL);assert(r >= 0);
	r = engine->RegisterObjectMethod("WidgetMgr", "void reload(string path)", asMETHOD(WidgetMgr, reloadXml), asCALL_THISCALL);assert(r >= 0);

	//register Widget class
	r = engine->RegisterObjectType("Widget", 0, asOBJ_REF);assert(r>=0);
	r = engine->RegisterObjectBehaviour("Widget", asBEHAVE_FACTORY, "Widget@ f()", asFUNCTION(Widget_Factory), asCALL_CDECL);assert(r >= 0);
	r = engine->RegisterObjectBehaviour("Widget", asBEHAVE_ADDREF, "void f()", asMETHOD(Widget, Addref), asCALL_THISCALL);assert(r>=0);
	r = engine->RegisterObjectBehaviour("Widget", asBEHAVE_RELEASE, "void f()", asMETHOD(Widget, Release), asCALL_THISCALL);assert(r>=0);
	r = engine->RegisterObjectMethod("Widget", "void test()", asMETHOD(Widget, test), asCALL_THISCALL);assert(r>=0);
	r = engine->RegisterObjectMethod("Widget", "void draw()", asMETHODPR(Widget, draw, (), void),
asCALL_THISCALL);assert(r>=0);
	r = engine->RegisterObjectMethod("Widget", "void draw(float c)", asMETHODPR(Widget, draw, (float), void), asCALL_THISCALL);assert(r>=0);
	r = engine->RegisterObjectMethod("Widget", "void draw(Point p)", asMETHODPR(Widget, draw, (Point), void), asCALL_THISCALL);assert(r>=0);
	r = engine->RegisterObjectMethod("Widget", "void draw(Point p, float c)", asMETHODPR(Widget, draw, (Point, float), void), asCALL_THISCALL);assert(r>=0);
	r = engine->RegisterObjectMethod("Widget", "int isInUI(Point p)", asMETHODPR(Widget, isInUI, (Point), int), asCALL_THISCALL);assert(r>=0);
	r = engine->RegisterObjectMethod("Widget", "int isInUI(float x, float y)", asMETHODPR(Widget, isInUI, (float, float), int), asCALL_THISCALL);assert(r>=0);
}

void ASEngine::RegisteEnum()
{
	int r;
	//register Enum RunStatus
	r = engine->RegisterEnum("RunStatus");assert(r>=0);
	r = engine->RegisterEnumValue("RunStatus", "Completed", Completed);assert(r>=0);
	r = engine->RegisterEnumValue("RunStatus", "Failure", Failure);assert(r>=0);
	r = engine->RegisterEnumValue("RunStatus", "Running", Running);assert(r>=0);

	//register Enum EnumTriggerType
	r = engine->RegisterEnum("EnumTriggerType");assert(r>=0);
	r = engine->RegisterEnumValue("EnumTriggerType", "kTrig_None", kTrig_None);assert(r>=0);
	r = engine->RegisterEnumValue("EnumTriggerType", "kTrig_LeftClickUp", kTrig_LeftClickUp);assert(r>=0);
	r = engine->RegisterEnumValue("EnumTriggerType", "kTrig_LeftClickDown", kTrig_LeftClickDown);assert(r>=0);
	r = engine->RegisterEnumValue("EnumTriggerType", "kTrig_RightClickUp", kTrig_RightClickUp);assert(r>=0);
	r = engine->RegisterEnumValue("EnumTriggerType", "kTrig_RightClickDown", kTrig_RightClickDown);assert(r>=0);
	r = engine->RegisterEnumValue("EnumTriggerType", "kTrig_KeyBroadUp", kTrig_KeyBroadUp);assert(r>=0);
	r = engine->RegisterEnumValue("EnumTriggerType", "KTrig_KeyBroadDown", KTrig_KeyBroadDown);assert(r>=0);
	r = engine->RegisterEnumValue("EnumTriggerType", "kTrig_RightMouseMove", kTrig_RightMouseMove);assert(r>=0);
	r = engine->RegisterEnumValue("EnumTriggerType", "kTrig_Left", kTrig_Left);assert(r>=0);
	r = engine->RegisterEnumValue("EnumTriggerType", "kTrig_Up", kTrig_Up);assert(r>=0);
	r = engine->RegisterEnumValue("EnumTriggerType", "kTrig_Right", kTrig_Right);assert(r>=0);
	r = engine->RegisterEnumValue("EnumTriggerType", "kTrig_Down", kTrig_Down);assert(r>=0);
}

void ASEngine::RegisteFunction()
{
	int r;
	r = engine->RegisterGlobalFunction("void Print(string &in)", asFUNCTION(PrintString), asCALL_CDECL  );assert(r >= 0);
	r = engine->RegisterGlobalFunction("void Print(float num)", asFUNCTION(PrintNum), asCALL_CDECL  );assert(r >= 0);
	r = engine->RegisterGlobalFunction("void yield()", asFUNCTION(yield), asCALL_CDECL  );assert(r>=0);
}

void ASEngine::scriptTest(string filepath)
{
	int r;
	FILE* f;
	fopen_s(&f, filepath.c_str(), "rb");
	assert(f);
	fseek(f, 0, SEEK_END);
	int len = ftell(f);
	fseek(f, 0, SEEK_SET);
	string script;
	script.resize(len);
	int c =	fread(&script[0], len, 1, f);assert(c);
	fclose(f);

	asIScriptModule *mod = engine->GetModule(0, asGM_ALWAYS_CREATE);
	r = mod->AddScriptSection("script", &script[0], len);assert(r >= 0);
	r = mod->Build();assert(r>=0);

	asIScriptFunction *func = engine->GetModule(0)->GetFunctionByDecl("void test()");assert(func);
	asIScriptContext* _ctx = engine->CreateContext();
	_ctx->Prepare(func);
	_ctx->Execute();
	_ctx->Prepare(_ctx->GetFunction());
	_ctx->Execute();
	_ctx->Release();
}

void ASEngine::Release()
{
	delete _instance;
}

ASEngine::~ASEngine()
{
	engine->Release();
}