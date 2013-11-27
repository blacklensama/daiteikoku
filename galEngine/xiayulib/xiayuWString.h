#pragma once
#include "xiayuObject.h"
#include "xiayuDouble.h"
namespace xiayuLib
{
	class xiayuWString:public xiayuObject
	{
	public:
		inline xiayuWString()
		{
			value = L"";
		}
		inline xiayuWString(WCHAR c)
		{
			value = c;
		}
		inline xiayuWString(const xiayuWString& s)
		{
			value = s.value;
		}
		inline xiayuWString(wstring s)
		{
			value = s;
		}
		inline xiayuWString& operator=(xiayuWString& s)
		{
			value = s.value;
			return *this;
		}
		inline xiayuWString& operator=(const wstring str)
		{
			value = str;
			return *this;
		}
		inline xiayuWString& operator=(const WCHAR c)
		{
			value = c;
			return *this;
		}
		inline xiayuWString& operator+=(const wstring str)
		{
			value += str;
			return *this;
		}
		inline xiayuWString& operator+=(const xiayuWString& str)
		{
			value += str.value;
			return *this;
		}
		inline WCHAR operator[](const int i)
		{
			return value[i];
		}
		inline operator wstring()
		{
			return value;
		}
		inline operator double()
		{
			return xiayuDouble::Parse(value);
		}
		inline wstring ToWString()
		{
			return value;
		}
		inline string ToString()
		{
			string temp(value.length(), ' ');
			std::copy(value.begin(), value.end(), temp.begin());
			return temp;
		}
		inline string GetType()
		{
			return "string";
		}
		inline int getSize()
		{
			return value.size();
		}
		inline vector<wstring> split(wstring str)
		{
			vector<wstring> temp;
			int i = 0;
			do 
			{
				wstring tmp;
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
		inline vector<wstring> split(WCHAR c)
		{
			wstring s;
			s += c;
			return this->split(s);
		}
		static wstring s2ws(string str)
		{
			return Ansi2WChar(str.c_str(),str.size());
		}
		~xiayuWString()
		{}
		wstring value;
	private:
		static wstring Ansi2WChar(LPCSTR pszSrc, int nLen)
		{
			int nSize = MultiByteToWideChar(CP_ACP, 0, (LPCSTR)pszSrc, nLen, 0, 0);
			if (nSize <= 0)
			{
				return NULL;
			}
			WCHAR* pwszDst = new WCHAR[nSize + 1];
			if (NULL == pwszDst)
			{
				return NULL;
			}
			MultiByteToWideChar(CP_ACP, 0,(LPCSTR)pszSrc, nLen, pwszDst, nSize);
			pwszDst[nSize] = 0;
			if( pwszDst[0] == 0xFEFF) // skip Oxfeff
				for(int i = 0; i < nSize; i ++) 
					pwszDst[i] = pwszDst[i+1]; 
			wstring wcharString(pwszDst);
			delete pwszDst;
			return wcharString;
		}
	};
	inline bool operator==(const xiayuWString& s1, const xiayuWString& s2)
	{
		return s1.value==s2.value;
	}
	inline bool operator==(const xiayuWString& s1, const wstring& s2)
	{
		return s1.value==s2;
	}
	inline bool operator!=(const xiayuWString& s1, const xiayuWString& s2)
	{
		return s1.value!=s2.value;
	}
	inline bool operator!=(const xiayuWString& s1, const wstring& s2)
	{
		return s1.value!=s2;
	}
	inline bool operator>(const xiayuWString& s1, const wstring& s2)
	{
		return s1.value>s2;
	}
	inline bool operator>(const xiayuWString& s1, const xiayuWString& s2)
	{
		return s1.value>s2.value;
	}
	inline bool operator>=(const xiayuWString& s1, const wstring& s2)
	{
		return s1.value>=s2;
	}
	inline bool operator>=(const xiayuWString& s1, const xiayuWString& s2)
	{
		return s1.value>=s2.value;
	}
	inline bool operator<(const xiayuWString& s1, const wstring& s2)
	{
		return s1.value<s2;
	}
	inline bool operator<(const xiayuWString& s1, const xiayuWString& s2)
	{
		return s1.value<s2.value;
	}
	inline bool operator<=(const xiayuWString& s1, const wstring& s2)
	{
		return s1.value<=s2;
	}
	inline bool operator<=(const xiayuWString& s1, const xiayuWString& s2)
	{
		return s1.value<=s2.value;
	}
	inline wstring operator+(const xiayuWString& s1, const wstring& s2)
	{
		return s1.value + s2;
	}
}