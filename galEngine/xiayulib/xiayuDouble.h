#pragma once
#include "xiayuObject.h"
namespace xiayuLib
{
	class xiayuDouble:public xiayuObject
	{
	public:
		inline xiayuDouble();
		inline xiayuDouble(double d):value(d)
		{}
		inline xiayuDouble(xiayuDouble& d):value(d.value)
		{}
		inline xiayuDouble& operator=(double f)
		{
			value = f;
			return *this;
		}
		inline xiayuDouble& operator=(xiayuDouble& f)
		{
			value = f.value;
			return *this;
		}
		inline ~xiayuDouble();
		inline operator double()
		{
			return value;
		}
		inline operator string()
		{
			return ToString();
		}
		inline string ToString()
		{
			stringstream ss;
			ss << value;
			string str;
			ss >> str;
			return str;
		}
		inline static double Parse(string str)
		{
			stringstream ss(str);
			double f = 0;
			ss >> f;
			return f;
		}
		inline static double Parse(wstring str)
		{
			wstringstream ss(str);
			double f = 0;
			ss >> f;
			return f;
		}
		inline string GetType()
		{
			return "double";
		}
		double value;
	private:

	};

	xiayuDouble::xiayuDouble()
	{
		value = 0;
	}

	xiayuDouble::~xiayuDouble()
	{
	}
}