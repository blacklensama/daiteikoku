#pragma once
#include "xiayuObject.h"
#include "xiayuDouble.h"
namespace xiayuLib
{
	class xiayuString:public xiayuObject
	{
	public:
		inline xiayuString()
		{
			value = "";
		}
		inline xiayuString(xiayuString& s)
		{
			value = s.value;
		}
		inline xiayuString(string s)
		{
			value = s;
		}
		inline xiayuString& operator=(xiayuString& s)
		{
			value = s.value;
			return *this;
		}
		inline xiayuString& operator=(const string str)
		{
			value = str;
			return *this;
		}
		inline xiayuString& operator+=(const string str)
		{
			value += str;
			return *this;
		}
		inline xiayuString& operator+=(const xiayuString& str)
		{
			value += str.value;
			return *this;
		}
		inline operator string()
		{
			return value;
		}
		inline operator double()
		{
			return xiayuDouble::Parse(value);
		}
		inline string ToString()
		{
			return value;
		}
		inline string GetType()
		{
			return "string";
		}
		inline vector<string> split(string str)
		{
			vector<string> temp;
			int i = 0;
			do 
			{
				string tmp;
				i = value.find(str);
				if (i == -1)
				{
					tmp = value.substr(0, value.length());
					temp.push_back(tmp);
					break;
				}
				tmp = value.substr(0, i);
				value.erase(0, i + 1);
				temp.push_back(tmp);
			} while (1);
			return temp;
		}
		inline vector<string> split(char c)
		{
			string s;
			s += c;
			return this->split(s);
		}
		inline ~xiayuString()
		{}
		string value;
	private:

	};
	inline bool operator==(const xiayuString& s1, const xiayuString& s2)
	{
		return s1.value==s2.value;
	}
	inline bool operator==(const xiayuString& s1, const string& s2)
	{
		return s1.value==s2;
	}
	inline bool operator!=(const xiayuString& s1, const xiayuString& s2)
	{
		return s1.value!=s2.value;
	}
	inline bool operator!=(const xiayuString& s1, const string& s2)
	{
		return s1.value!=s2;
	}
	inline bool operator>(const xiayuString& s1, const string& s2)
	{
		return s1.value>s2;
	}
	inline bool operator>(const xiayuString& s1, const xiayuString& s2)
	{
		return s1.value>s2.value;
	}
	inline bool operator>=(const xiayuString& s1, const string& s2)
	{
		return s1.value>=s2;
	}
	inline bool operator>=(const xiayuString& s1, const xiayuString& s2)
	{
		return s1.value>=s2.value;
	}
	inline bool operator<(const xiayuString& s1, const string& s2)
	{
		return s1.value<s2;
	}
	inline bool operator<(const xiayuString& s1, const xiayuString& s2)
	{
		return s1.value<s2.value;
	}
	inline bool operator<=(const xiayuString& s1, const string& s2)
	{
		return s1.value<=s2;
	}
	inline bool operator<=(const xiayuString& s1, const xiayuString& s2)
	{
		return s1.value<=s2.value;
	}
	inline string operator+(const xiayuString& s1, const string& s2)
	{
		return s1.value + s2;
	}
}