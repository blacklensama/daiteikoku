#pragma once
#include "xiayuObject.h"
namespace xiayuLib
{
	class xiayuWChar:public xiayuObject
	{
	public:
		inline xiayuWChar();
		inline xiayuWChar(const WCHAR c):value(c)
		{}
		inline xiayuWChar(const xiayuWChar& c):value(c.value)
		{}
		inline xiayuWChar& operator=(const WCHAR c)
		{
			value = c;
			return *this;
		}
		inline xiayuWChar& operator=(const xiayuWChar& c)
		{
			value = c.value;
			return *this;
		}
		inline string ToString()
		{
			string str;
			str += value;
			return str;
		}
		inline string GetType()
		{
			return "char";
		}
		inline static char Parse(string str)
		{
			if (str.size() == 0)
			{
				return 0;
			}
			return str[0];
		}
		inline operator string()
		{
			return ToString();
		}
		inline operator WCHAR()
		{
			return value;
		}
		inline ~xiayuWChar();
		WCHAR value;
	private:

	};

	xiayuWChar::xiayuWChar()
	{
		value = 0;
	}

	xiayuWChar::~xiayuWChar()
	{
	}
}