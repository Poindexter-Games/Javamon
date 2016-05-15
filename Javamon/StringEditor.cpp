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

int StringEditor::getFirstAppearanceIn(wstring w, wchar_t c)
{
	for (int i = 0; i < w.length(); i++) 
	{
		if (w[i] == c)
		{
			return i;
		}
	}

	return -1;
}

wstring StringEditor::substring(wstring wstr, int beginIndex, int endIndex)
{
	wstring w;

	for (int i = beginIndex; i < endIndex; i++)
	{
		w += wstr[i];
	}

	return w;
}

bool StringEditor::startsWith(wstring wstr, wstring pre)
{
	if (pre.length() > wstr.length())
	{
		return false;
	}
	for (int i = 0; i < pre.length(); i++)
	{
		if(wstr[i] != pre[i])
		{
			return false;
		}
	}
	return true;
}

int StringEditor::findCharacter(wstring str, wchar_t c, int n)
{
	int occurence = 0;

	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] == c)
		{
			occurence++;
			if (occurence == n)
			{
				//If the occurence = n, return character location
				return i;
			}
		}
	}

	//Return -1 if the character was never found
	return -1;
}

wstring StringEditor::getString(wstring w, int n)
{
	wstring str = L"";
	int occurence = 0;
	int openQuote = 0;
	int closeQuote = 1;

	for (int i = 0; i < w.length(); i++)
	{
		if(w[i] == L'\"' && w[i - 1] != L'\\')
		{
			occurence++;
			if ((occurence - (occurence % 2)) / 2 == n)
			{
				openQuote = i;
			}
			if (occurence = n * 2 + 1)
			{
				closeQuote = i;
			}
		}
	}

	return substring(w, openQuote + 1, closeQuote);
}