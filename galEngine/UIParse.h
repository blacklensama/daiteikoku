#pragma once

#include "stdafx.h"

struct UIscript
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

class UIParse
{
public:
	void init(wstring str);
	void load_the_txt(wstring filename);
	UIscript read_next_script();
	wstring parse();
private:
	wifstream infile;
	UIscript s;
};