#pragma once
#include "xiayuObject.h"

namespace xiayuLib
{
	class xiayuInt:public xiayuObject
	{
	public:
		inline xiayuInt()
		{
			value = 0;
		}
		inline xiayuInt(const xiayuInt& i)
		{
			value = i.value;
		}
		inline xiayuInt(int i)
		{
			value = i;
		}
		inline ~xiayuInt(){}
		int value;
		inline xiayuInt& operator=(const int i)
		{
			value = i;
			return *this;
		}
		inline xiayuInt& operator=(const xiayuInt& i)
		{
			value = i.value;
			return *this;
		}
		inline xiayuInt& operator++(const int i)
		{
			value++;
			return *this;
		}
		inline static int Parse(string str)
		{
			stringstream ss(str);
			int i = 0;
			ss >> i;
			return i;
		}
		inline string ToString()
		{
			stringstream ss;
			ss << value;
			string str;
			ss >> str;
			return str;
		}
		inline operator string()
		{
			return ToString();
		}
		inline operator int()
		{
			return value;
		}
	private:

	};

/*
	bool operator==(const int i,const xiayuInt& j)
	{
		return i == j.value;
	}

	bool operator==(const xiayuInt& i, const xiayuInt& j)
	{
		return i.value == j.value;
	}

	bool operator!=(const xiayuInt& i, const xiayuInt& j)
	{
		return i.value != j.value;
	}

	bool operator!=(const xiayuInt& i, const int j)
	{
		return i.value != j;
	}

	bool operator>(const xiayuInt& i, const xiayuInt& j)
	{
		return i.value >j.value;
	}
	bool operator>(const xiayuInt& i, const int& j)
	{
		return i.value >j;
	}
	bool operator>=(const xiayuInt& i, const xiayuInt& j)
	{
		return i.value >= j.value;
	}
	bool operator>=(const xiayuInt& i, const int& j)
	{
		return i.value >= j;
	}
	bool operator<(const xiayuInt& i, const xiayuInt& j)
	{
		return i.value<j.value;
	}
	bool operator<(const xiayuInt& i, const int& j)
	{
		return i.value< j;
	}
	bool operator<=(const xiayuInt& i, const xiayuInt& j)
	{
		return i.value<=j.value;
	}
	bool operator<=(const xiayuInt& i, const int& j)
	{
		return i.value<= j;
	}*/
}