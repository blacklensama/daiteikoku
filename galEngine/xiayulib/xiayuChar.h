#pragma once
#include "xiayuObject.h"
namespace xiayuLib
{
	class xiayuChar:public xiayuObject
	{
	public:
		inline xiayuChar();
		inline xiayuChar(const char c):value(c)
		{}
		inline xiayuChar(const xiayuChar& c):value(c.value)
		{}
		inline xiayuChar& operator=(const char c)
		{
			value = c;
			return *this;
		}
		inline xiayuChar& operator=(const xiayuChar& c)
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
		inline operator char()
		{
			return value;
		}
		inline ~xiayuChar();
		char value;
	private:

	};

	xiayuChar::xiayuChar()
	{
		value = 0;
	}

	xiayuChar::~xiayuChar()
	{
	}
}