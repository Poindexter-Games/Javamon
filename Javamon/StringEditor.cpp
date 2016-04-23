#include "StringEditor.h"

//DESCRIPTONS ARE IN THE HEADER FILE

bool StringEditor::equals(sf::String str, wstring wstr)
{
	return str.toWideString().compare(wstr) == 0;
}


void StringEditor::echo(wstring str)
{
	wcout << str << endl;
}
void StringEditor::echo(int i)
{
	wcout << i << endl;
}
void StringEditor::echo(float f)
{
	wcout << f << endl;
}
void StringEditor::echo(wstring str, int i)
{
	wcout << str << L" " << i << endl;
}
void StringEditor::echo(int i, wstring str)
{
	wcout << i << L" " << str << endl;
}

int StringEditor::getFirstAppearanceOf(char c, sf::String s)
{
	for (int i = 0; i < s.toWideString().length(); i++) 
	{
		if (s[i] == c)
		{
			return i;
		}
	}

	return -1;
}
