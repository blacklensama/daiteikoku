#include "behavior_tree.h"
#include "EnumUtil.h"
#include<stdlib.h> 
int main()
{
	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF|_CRTDBG_ALLOC_MEM_DF);
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
	EnumUtil::init();
	ASEngine* en = ASEngine::Instance();
	en->scriptTest("test.as");
	BehaviorTreeObject obj;
	auto i = obj.loadFromXml("btree/test.xml");
	delete i;
	en->Release();
	BlackBoardForScript::Release();
}