#include "ASFunction.h"
void PrintString(string &str)
{
	cout << str;
}

void yield()
{
	asIScriptContext *ctx = asGetActiveContext();
	if (ctx)
	{
		ctx->Suspend();
	}
}

void PrintNum(float num)
{
	cout << num << endl;
}

BlackBoardForScript* getBlackBoard()
{
	return BlackBoardForScript::Instance();
}
