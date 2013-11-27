#pragma once
#include "xiayuObject.h"
namespace xiayuLib
{
	class xiayuFloat:public xiayuObject
	{
	public:
		inline xiayuFloat()
		{
			value = 0;
		}
		inline xiayuFloat(float f)
		{
			value = f;
		}
		inline xiayuFloat(xiayuFloat& f)
		{
			value = f.value;
		}
		inline operator float()
		{
			return value;
		}
		inline operator string()
		{
			return ToString();
		}
		inline xiayuFloat& operator=(const float f)
		{
			value = f;
			return *this;
		}
		inline xiayuFloat& operator=(const xiayuFloat& f)
		{
			value = f.value;
			return *this;
		}
		inline static float Parse(string str)
		{
			stringstream ss(str);
			float f = 0;
			ss >> f;
			return f;
		}
		inline string ToString()
		{
			stringstream ss;
			ss >> value;
			string str;
			ss << str;
			return str;
		}
		inline string GetType()
		{
			return "float";
		}
		inline ~xiayuFloat()
		{}
		float value;
	private:

	};
	/*bool operator>(const xiayuFloat& f1, const xiayuFloat& f2)
	{
		return f1.value > f2.value;
	}
	bool operator>=(const xiayuFloat& f1, const xiayuFloat& f2)
	{
		return f1.value >= f2.value;
	}
	bool operator==(const xiayuFloat& f1, const xiayuFloat& f2)
	{
		return f1.value == f2.value;
	}
	bool operator<=(const xiayuFloat& f1, const xiayuFloat& f2)
	{
		return f1.value <= f2.value;
	}
	bool operator<(const xiayuFloat& f1, const xiayuFloat& f2)
	{
		return f1.value < f2.value;
	}

	bool operator>(const xiayuFloat& f1, const float f2)
	{
		return f1.value > f2;
	}
	bool operator>=(const xiayuFloat& f1, const float f2)
	{
		return f1.value >= f2;
	}
	bool operator==(const xiayuFloat& f1, const float f2)
	{
		return f1.value == f2;
	}
	bool operator<=(const xiayuFloat& f1, const float f2)
	{
		return f1.value <= f2;
	}
	bool operator<(const xiayuFloat& f1, const float f2)
	{
		return f1.value < f2;
	}*/
}