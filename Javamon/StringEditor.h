#pragma once

#include <string>
#include <iostream>

using namespace std;

class StringEditor
{
private:
public:
	static wstring popOffParameter(wstring & line)
	{
		echo(L"=====START OF POP OFF PARAMETER=====");
		int comma_pos = -1;
		echo(L"Line: " + line);
		for (int i = 0; i < line.length(); i++)
		{
			if ((line[i] == L',') || (line[i] == L';'))
			{
				echo(to_wstring(line[i]) + L" found at " + to_wstring(i));
				comma_pos = i;
				break;
			}
		}
		wchar_t* param = new wchar_t[comma_pos + 1];
		for (int i = 0; i < comma_pos; i++)
		{
			param[i] = line[i];
		}
		param[comma_pos] = L'\0';
		wstring paramstr = param;
		echo(L"Parameter: " + paramstr);
		wchar_t* newLine = new wchar_t[(line.length() - comma_pos - 1) + 1];
		for (int i = comma_pos + 1; i < line.length(); i++)
		{
			newLine[i - (comma_pos + 1)] = line[i];
		}
		newLine[line.length() - comma_pos] = L'\0';
		line = newLine;
		echo(L"New Line : " + line);
		echo(L"=====END OF POP OFF PARAMETER=====");
		return param;
	}

	static void echo(wstring line)
	{
		wcout << line << endl;
	}
	static void echo(int line)
	{
		wcout << line << endl;
	}
};