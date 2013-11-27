#pragma once

#include "stdafx.h"

struct script
{
	PARSE kind;
	xiayuWString file;
	xiayuFloat x;
	xiayuFloat y;
	xiayuWString stlye;
	xiayuInt layer;
	xiayuWString str;
	vector<xiayuWString> chance;
	xiayuWString color;
};

class Parse
{
public:
	static void init();
	static void load_the_txt(wstring filename);
	static script read_next_script();
	static wstring parse();
private:
	static wifstream infile;
	static script s;
};