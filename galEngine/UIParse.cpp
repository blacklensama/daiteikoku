#include "UIParse.h"

void UIParse::init(wstring str)
{
	infile.open(str.c_str());
	infile.imbue(locale(".936"));
}

void UIParse::load_the_txt(wstring filename)
{
	infile.close();
	infile.open(filename.c_str());
	infile.imbue(locale(".936"));
}

UIscript UIParse::read_next_script()
{
	xiayuWString temp;
	temp = parse();
	if (temp == L"<drawbg>")
	{
		s.kind = PARSE::drawbg;
		temp = parse();
		s.file = temp;
		temp = parse();
		s.x = temp;
		temp = parse();
		s.y = temp;
		temp = parse();
		if (temp == L"style")
		{
			s.stlye = parse();
		}
		parse();
	}else if (temp == L"<draw>")
	{
		s.kind = PARSE::draw;
		temp = parse();
		s.layer = temp;
		temp = parse();
		s.file = temp;
		temp = parse();
		s.x = temp;
		temp = parse();
		s.y = temp;
		temp = parse();
		if (temp == L"style")
		{
			s.stlye = parse();
		}
		parse();
	}else if (temp == L"<clear>")
	{
		s.kind = PARSE::clear;
		temp = parse();
		s.layer = temp;
		parse();
	}else if (temp == L"<print>")
	{
		s.kind = PARSE::print;
		s.str = parse();
		temp = parse();
		if (temp == L"color")
		{
			s.color = parse();
		}
		parse();
	}else if (temp == L"<printEx>")
	{
		s.kind = PARSE::printEx;
		s.str = parse();
		temp = parse();
		s.x = temp;
		temp = parse();
		s.y = temp;
		temp = parse();
		if (temp == L"color")
		{
			s.color = parse();
		}
		parse();
	}else if (temp == L"<wait>")
	{
		s.kind = PARSE::wait;
		parse();
	}else if (temp == L"<bgm>")
	{
		s.kind = PARSE::bgm;
		temp = parse();
		s.file = temp;
		parse();
	}else if (temp == L"<voice>")
	{
		s.kind = PARSE::voice;
		temp = parse();
		s.file = temp;
		parse();
	}else if (temp == L"<goto>")
	{
		s.kind = PARSE::Goto;
		s.chance.swap(vector<xiayuWString>());
		while (1)
		{
			temp = parse();
			if (temp == L"</goto>")
			{
				break;
			}
			s.chance.push_back(temp);
		}
		parse();
	}else if (temp == L"<end>")
	{
		s.kind = PARSE::end;
		parse();
	}
	return s;
}

wstring UIParse::parse()
{
	wstring str;
	WCHAR c;
	while (infile.get(c))
	{
		if (c == L' ')
		{
			continue;
		}else if (c == L'\t')
		{
			continue;
		}else if (c == L'\n')
		{
			continue;
		}
		if (c == L'<')
		{
			while (c != L'>')
			{
				str += c;
				infile.get(c);	
			}
			str += c;
			break;
		}
		if (c == L'"')
		{
			infile.get(c);
			while (c != L'"')
			{
				str += c;
				infile.get(c);
			}
			break;
		}
		if (iswdigit(c))
		{
			while (iswdigit(c))
			{
				str += c;
				infile.get(c);
			}
			break;
		}
		if (iswalpha(c))
		{
			while (iswalpha(c))
			{
				str += c;
				infile.get(c);
			}
			break;
		}
	}
	return str;
}