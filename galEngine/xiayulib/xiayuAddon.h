#pragma once

#include "xiayuObject.h"
#include "xiayuWString.h"

namespace xiayuLib
{
	static int xy_wchar_to_16(WCHAR c)
	{
		switch (c)
		{
		case L'0':
			return 0;
		case L'1':
			return 1;
		case L'2':
			return 2;
		case L'3':
			return 3;
		case L'4':
			return 4;
		case L'5':
			return 5;
		case L'6':
			return 6;
		case L'7':
			return 7;
		case L'8':
			return 8;
		case L'9':
			return 9;
		case L'A':
			return 10;
		case L'B':
			return 11;
		case L'C':
			return 12;
		case L'D':
			return 13;
		case L'E':
			return 14;
		case L'F':
			return 15;
		}
	}

	static vector<xiayuString>  xy_find_filename(const char* file)
	{
		vector<xiayuString> temp;
		WIN32_FIND_DATAA fd;

		HANDLE hFind = FindFirstFileA(file, &fd);

		if (hFind != INVALID_HANDLE_VALUE)
		{
			do 
			{
				temp.push_back(xiayuString(fd.cFileName));
			} while (FindNextFileA(hFind, &fd));
			FindClose(hFind);
		}
		return temp;
	}

	static vector<xiayuWString> xy_find_filename(const WCHAR* file)
	{
		xiayuWString temp1(file);
		temp1 = temp1.split(L'\\')[0] + L"\\";
		vector<xiayuWString> temp;
		WIN32_FIND_DATA fd;

		HANDLE hFind = FindFirstFile(file, &fd);

		if (hFind != INVALID_HANDLE_VALUE)
		{
			do 
			{
				temp.push_back(temp1 + xiayuWString(fd.cFileName));
			} while (FindNextFile(hFind, &fd));
			FindClose(hFind);
		}
		return temp;
	}
}