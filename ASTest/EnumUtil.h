#include "stdafx.h"

class EnumUtil
{
public:
	static void RegisterEnumValue(string str, int num);
	static int getEnumValue(string str);
	static void init();
protected:
private:
	static map<string, int> EnumReflection;
};