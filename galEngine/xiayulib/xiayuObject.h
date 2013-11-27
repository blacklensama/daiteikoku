#pragma once
#include "stdafx.h"
namespace xiayuLib
{
	class xiayuObject
	{
	public:
		inline xiayuObject();
		inline virtual ~xiayuObject();
		inline virtual string ToString();
		inline virtual wstring ToWString();
		inline virtual string GetType();
	private:

	};

	xiayuObject::xiayuObject()
	{
	}

	string xiayuObject::ToString()
	{
		return "Object";
	}

	wstring xiayuObject::ToWString()
	{
		return L"only for wstring";
	}

	string xiayuObject::GetType()
	{
		return "Object";
	}

	xiayuObject::~xiayuObject()
	{
	}
}